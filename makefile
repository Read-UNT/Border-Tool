color: main.o
	g++  -o color main.o

main.o: main.cpp main.h
	g++ -std=c++11 -c main.cpp