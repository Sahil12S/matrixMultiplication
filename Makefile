CC = g++
CFLAGS = -std=c++11 -O

default = matrix

matrx: main.o
		$(CC) $(CFLAGS) -o matrix main.o

main.o: main.cpp Matrix.hpp
		$(CC) $(VERSION) $(CFLAGS) -c main.cpp

clean: 
	-rm *.o matrix