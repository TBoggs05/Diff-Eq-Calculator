CC = clang++ -std=c++11

all: mainRunner

mainRunner: main.o eulers.o
	$(CC) -o mainRunner eulers.o main.o

main.o: main.cpp
	$(CC) -c main.cpp


eulers.o: eulers.cpp eulers.h
	$(CC) -c eulers.cpp 



clean:
	rm -rf *.o
	rm -rf mainRunner