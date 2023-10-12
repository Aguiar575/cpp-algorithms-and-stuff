//Arrays in C++
//An array is a data structure that stores a collection of elements of the same data type. 
//Arrays are declared by specifying the data type of the elements and the size of the array. 

#include <iostream>

int main() {
  int my_array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // Print all of the elements in the array to the console.
  for (int i = 0; i < 10; i++) {
    std::cout << my_array[i] << std::endl;
  }

  return 0;
}

