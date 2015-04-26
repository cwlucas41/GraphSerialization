all: graphTest

GDFFormat.o: GDFFormat.cpp GDFFormat.h graph.h
	g++ -std=c++11 -c GDFFormat.cpp

DOTFormat.o: DOTFormat.cpp DOTFormat.h graph.h
	g++ -std=c++11 -c DOTFormat.cpp

graphTest.o: graphTest.cpp grlist.h grmat.h graphutil.cpp DOTFormat.h GDFFormat.h
	g++ -std=c++11 -c graphTest.cpp

graphTest: graphTest.o DOTFormat.o GDFFormat.o
	g++  -std=c++11 graphTest.o GDFFormat.o DOTFormat.o -o graphTest

clean:
	rm *.o
	rm graph

cleanGraphs:
	rm *.dot
	rm *.gdf
