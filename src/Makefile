CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -fsanitize=address

all: main

main: main.o
	$(CC) $(FLAGS) -o ../build/program main.o

main.o: main.cpp Sequence.hpp ArraySequence.hpp DynamicArray.hpp ListSequence.hpp LinkedList.hpp Sorter.hpp
	$(CC) $(FLAGS) -c main.cpp

clean:
	rm -rf *.o *.gch ../build/program

rebuild: clean all
