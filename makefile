all: graph

main.o: main.cpp grlist.h grmat.h graphutil.cpp
	g++ -std=c++11 -c main.cpp

graph: main.o
	g++  main.o -o graph

clean:
	rm *.o
