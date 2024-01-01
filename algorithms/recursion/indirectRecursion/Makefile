CC=g++
CFLAGS=-std=c++17 -Wall -Wextra -pthread
EXECUTABLE=search_program

all: $(EXECUTABLE)

$(EXECUTABLE): indirectRecursion.cpp
	$(CC) $(CFLAGS) indirectRecursion.cpp -o $@

clean:
	rm -f $(EXECUTABLE)

