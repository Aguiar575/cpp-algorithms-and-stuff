build: main_lib.o main.o
	g++ main.o main_lib.o -o main

main.o:
	g++ main.cc -c

main_lib.o:
	g++ main_lib.cc -c

execute:
	./main

clean:
	rm -f *.o
	rm -f main
