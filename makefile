all: graph

GDFFormat.o: GDFFormat.cpp GDFFormat.h graph.h
	g++ -std=c++11 -c GDFFormat.cpp

DOTFormat.o: DOTFormat.cpp DOTFormat.h graph.h
	g++ -std=c++11 -c DOTFormat.cpp

main.o: main.cpp grlist.h grmat.h graphutil.cpp DOTFormat.h GDFFormat.h
	g++ -std=c++11 -c main.cpp

graph: main.o DOTFormat.o GDFFormat.o
	g++  -std=c++11 main.o GDFFormat.o DOTFormat.o -o graph

clean:
	rm *.o
	rm graph

cleanGraphs:
	rm *.dot
	rm *.gdf
