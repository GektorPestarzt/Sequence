CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra
FLAGS2=-fsanitize=address

all: main

main: main.o
	$(CC) $(FLAGS) -o ../build/program main.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp -std=c++11

clean:
	rm -rf *.o *.gch ../build/program

rebuild: clean all
