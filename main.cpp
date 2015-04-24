//
//  main.cpp
//  GraphSerialization
//
//  Created by Christopher Lucas on 4/15/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <functional>
#include "grlist.h"
#include "grmat.h"
#include "graphutil.cpp"
using namespace std;

void checkEdge(Graph* g, int v1, int v2, int weight){
	if (!g->isEdge(v1,v2)) {
		cout << v1 << ", " << v2 << " is not an edge" << endl;
		return;
	}
	int actualWeight = g->weight(v1,v2);
	if (actualWeight != weight) {
		cout << "Edge " << v1 << ", " << v2 << " has weight " << actualWeight << ". The weight should be " << weight << "." << endl;
	}
}

void graphSumSetter(Graph* g, int n, function<int(int, int)> w, function<bool(int,int)> acc){
for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			int weight = w(i,j);
			if (weight > 0 && acc(i,j)) {
				g->setEdge(i, j, weight);
			}
		}
	}
}

void graphSumChecker(Graph* g, int n, function<int(int, int)> w, function<bool(int,int)> acc){
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			int weight = w(i,j);
			if (weight > 0 && acc(i,j)) {
				checkEdge(g, i, j, weight);
			}
		}
	}
}

template <typename GraphImplementation>
void testLinearization(int n, string fileName, function<int(int,int)> weightFunction, function<bool(int,int)> edgeCriteria) {
	ifstream fin;
	ofstream fout;
	
	fout.open(fileName);
	GraphImplementation outGraph(n);
	graphSumSetter(&outGraph, n, weightFunction, edgeCriteria);
	outGraph.serialize(fout);
	fout.close();
	
	fin.open(fileName);
	GraphImplementation inGraph(n);
	inGraph.deserialize(fin);
	graphSumChecker(&inGraph, n, weightFunction, edgeCriteria);
	fin.close();
}

int main(int argc, const char * argv[]) {
	
	int size = 5;
	
	function<int(int,int)> weightFunction = [size] (int x, int y) {return x+y+size;};
	
	function<bool(int,int)> sparseEdgeCriteria = [size] (int x, int y) {
		int d = ceil(sqrt(size));
		return x%d == 0 && y%d == 0;
	};
	
	function<bool(int,int)> denseEdgeCriteria = [size] (int x, int y) -> bool {return true;};
	
	testLinearization<Graphl>(size, "graphl.dot", weightFunction, sparseEdgeCriteria);
	testLinearization<Graphm>(size, "graphm.dot", weightFunction, denseEdgeCriteria);
	
	// test GDFdeserialize()
	ifstream fin;
	fin.open("GDFexample.gdf");
	Graphl gdfImport(size);
	gdfImport.GDFdeserialize(fin);
	Gprint(&gdfImport);
	fin.close();
	
	Graphm test(0);
	test.resize(size);
	if (size != test.n()) {
		cout << "Resize failed" << endl;
	}
	
	return 0;
}
