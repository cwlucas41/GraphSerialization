all: graphLinearizationTest graphEfficiencyTest

GDFFormat.o: GDFFormat.cpp GDFFormat.h graph.h
	g++ -std=c++11 -c GDFFormat.cpp

DOTFormat.o: DOTFormat.cpp DOTFormat.h graph.h
	g++ -std=c++11 -c DOTFormat.cpp

dijkstra.o: dijkstra.cpp book.h grlist.h heap.h
	g++ -std=c++11 -c dijkstra.cpp

graphutil.o: graphutil.cpp graph.h
	g++ -std=c++11 -c graphutil.cpp

graphEfficiencyTest.o: graphEfficiencyTest.cpp
	g++ -std=c++11 -c graphEfficiencyTest.cpp

graphLinearizationTest.o: graphLinearizationTest.cpp grlist.h grmat.h graphutil.cpp DOTFormat.h GDFFormat.h
	g++ -std=c++11 -c graphLinearizationTest.cpp

graphLinearizationTest: graphLinearizationTest.o DOTFormat.o GDFFormat.o graphutil.o
	g++  -std=c++11 graphLinearizationTest.o DOTFormat.o GDFFormat.o graphutil.o -o graphLinearizationTest

graphEfficiencyTest: graphEfficiencyTest.o DOTFormat.o GDFFormat.o graphutil.o dijkstra.o
	g++ -std=c++11 graphEfficiencyTest.o DOTFormat.o GDFFormat.o graphutil.o dijkstra.o -o graphEfficiencyTest

clean:
	rm *.o
	rm graphLinearizationTest
	rm graphEfficiencyTest

cleanGraphs:
	rm *.dot
	rm *.gdf
