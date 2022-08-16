CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -fsanitize=address

all: array_sequence

array_sequence: main.o
	$(CC) $(FLAGS) -o ../build/program main.o

main.o: main.cpp ArraySequence.hpp Sequence.hpp DynamicArray.hpp
	$(CC) $(FLAGS) -c main.cpp

clean:
	rm -rf *.o *.gch ../build/program

rebuild: clean all
