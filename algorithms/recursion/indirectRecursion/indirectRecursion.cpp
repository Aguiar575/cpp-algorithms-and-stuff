#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::string to_lower(const std::string &str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

std::string get_file_name(const std::string &file_path) {
  size_t last_slash = file_path.find_last_of('/');
  return (last_slash != std::string::npos) ? file_path.substr(last_slash + 1)
                                           : file_path;
}

size_t get_file_size(const std::string &file_path) {
  std::ifstream file(file_path, std::ios::binary | std::ios::ate);
  return file.is_open() ? static_cast<size_t>(file.tellg()) : 0;
}


void display_file_info(const std::string &file_path, size_t line_number,
        const std::vector<std::string> &content) {
    std::string file_name = get_file_name(file_path);
    std::string file_size = std::to_string(get_file_size(file_path));

    std::cout << "\nFile: " << file_name << std::endl;
    std::cout << "Path: " << file_path << std::endl;
    std::cout << "Size: " << file_size << " bytes" << std::endl;
    std::cout << "Keywords Found at Line " << line_number << ": "
        << content[line_number - 1] << std::endl;
}

void search_file_for_keywords(const std::string &file_path,
                              const std::vector<std::string> &keywords,
                              bool case_sensitive, std::mutex &display_mutex) {
  std::ifstream file(file_path);
  std::string line;
  std::vector<std::string> content;

  if (!file.is_open()) {
    std::lock_guard<std::mutex> lock(display_mutex);
    std::cerr << "Error reading file " << file_path << std::endl;
    return;
  }

  while (std::getline(file, line)) {
    content.push_back(line);
  }

  for (size_t line_number = 1; line_number <= content.size(); ++line_number) {
    for (const auto &keyword : keywords) {
      std::string search_line = case_sensitive
                                    ? content[line_number - 1]
                                    : to_lower(content[line_number - 1]);
      std::string search_keyword = case_sensitive ? keyword : to_lower(keyword);

      if (search_line.find(search_keyword) != std::string::npos) {
        std::lock_guard<std::mutex> lock(display_mutex);
        display_file_info(file_path, line_number, content);
        break;
      }
    }
  }
}

void search_files_in_directory(const std::string &directory,
                               const std::string &file_extension,
                               const std::vector<std::string> &keywords,
                               bool case_sensitive, std::mutex &mutex) {

  std::cout << "I'm in: " + directory << std::endl;

  try {
    for (const auto &entry : std::filesystem::directory_iterator(directory)) {
      const std::string &item_path = entry.path().string();

      if (entry.is_directory()) {
        std::thread(search_files_in_directory, item_path, file_extension,
                    std::ref(keywords), case_sensitive, std::ref(mutex))
            .detach();
      } else if (entry.is_regular_file()) {
        if (entry.path().extension() == file_extension) {
          std::thread(search_file_for_keywords, item_path, std::ref(keywords),
                      case_sensitive, std::ref(mutex))
              .detach();
        }
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "An error occurred: " << e.what() << std::endl;
  }
}

int main() {
  std::string current_directory = std::filesystem::current_path().string();
  std::vector<std::string> keywords = {"example", "cpp", "search"};
  std::mutex mutex;

  search_files_in_directory(current_directory, ".txt", keywords, false, mutex);
  std::this_thread::sleep_for(std::chrono::seconds(5));

  return 0;
}
