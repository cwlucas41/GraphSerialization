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
#include "DOTFormat.h"
#include "GDFFormat.h"
using namespace std;


template <typename GraphImplementation>
void testLinearization(int n, string fileName, Serializer* format, function<int(int,int)> weightFunction, function<bool(int,int)> edgeCriteria);

void graphSumChecker(Graph* g, int n, function<int(int, int)> w, function<bool(int,int)> acc);

void graphSumSetter(Graph* g, int n, function<int(int, int)> w, function<bool(int,int)> acc);

void checkEdge(Graph* g, int v1, int v2, int weight);


int main(int argc, const char * argv[]) {
	
	DOTFormat dotFormat;
	GDFFormat gdfFormat;
	int size = 100;
	function<int(int,int)> weightFunction = [size] (int x, int y) {return x+y+size;};
	function<bool(int,int)> sparseEdgeCriteria = [size] (int x, int y) {
		int d = ceil(sqrt(size));
		return x%d == 0 && y%d == 0;
	};
	function<bool(int,int)> denseEdgeCriteria = [size] (int x, int y) -> bool {return true;};
	
	Graphm test(0);
	test.resize(size);
	if (size != test.n()) {
		cout << "Resize failed" << endl;
	}
	
	testLinearization<Graphl>(size, "l.dot", &dotFormat, weightFunction, sparseEdgeCriteria);
	testLinearization<Graphm>(size, "m.dot", &dotFormat, weightFunction, sparseEdgeCriteria);
	testLinearization<Graphl>(size, "l.gdf", &gdfFormat, weightFunction, sparseEdgeCriteria);
	testLinearization<Graphm>(size, "m.gdf", &gdfFormat, weightFunction, sparseEdgeCriteria);
	
	return 0;
}


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
void testLinearization(int n, string fileName, Serializer* format, function<int(int,int)> weightFunction, function<bool(int,int)> edgeCriteria) {
	ifstream fin;
	ofstream fout;
	
	fout.open(fileName);
	GraphImplementation outGraph(n);
	graphSumSetter(&outGraph, n, weightFunction, edgeCriteria);
	outGraph.serialize(fout, format);
	fout.close();
	
	fin.open(fileName);
	GraphImplementation inGraph(0); // graph is, in general, the incorrect size. Deserialize should fix this and an error should not be produced.
	inGraph.deserialize(fin, format);
	graphSumChecker(&inGraph, n, weightFunction, edgeCriteria);
	fin.close();
}

