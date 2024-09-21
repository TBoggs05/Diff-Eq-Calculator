CC = clang++ 
CCFLAGS = -std=c++17 -Wall -I ../Crow/include -I /opt/homebrew/Cellar/asio/1.30.2/include -pthread
all: mainRunner

mainRunner: main.o eulers.o
	$(CC) $(CCFLAGS) -o mainRunner eulers.o main.o

main.o: main.cpp
	$(CC) $(CCFLAGS) -c main.cpp


eulers.o: eulers.cpp eulers.h
	$(CC) $(CCFLAGS) -c eulers.cpp 



clean:
	rm -rf *.o
	rm -rf mainRunner