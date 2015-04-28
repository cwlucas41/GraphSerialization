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
#include "Functions.h"
#include "grlist.h"
#include "grmat.h"
#include "DOTFormat.h"
#include "GDFFormat.h"
#include "graphutil.h"
using namespace std;


template <typename GraphImplementation>
void testLinearization(int n, string fileName, Serializer* format, function<int(int, int,int)> weightFunction, function<bool(int, int,int)> edgeCriteria);

void graphChecker(Graph* g, int n, function<int(int, int,int)> w, function<bool(int, int,int)> acc);

void graphSetter(Graph* g, int n, function<int(int, int,int)> w, function<bool(int, int,int)> acc);

void checkEdge(Graph* g, int v1, int v2, int weight);


int main(int argc, const char * argv[]) {
	
	DOTFormat dotFormat;
	GDFFormat gdfFormat;
	int size = 10;

	
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

void graphSetter(Graph* g, int n, function<int(int,int,int)> w, function<bool(int,int,int)> acc){
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			int weight = w(i,j,n);
			if (weight > 0 && acc(i,j,n)) {
				g->setEdge(i, j, weight);
			}
		}
	}
}

void graphChecker(Graph* g, int n, function<int(int,int,int)> w, function<bool(int,int,int)> acc){
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			int weight = w(i,j,n);
			if (weight > 0 && acc(i,j,n)) {
				checkEdge(g, i, j, weight);
			}
		}
	}
}

template <typename GraphImplementation>
void testLinearization(int n, string fileName, Serializer* format, function<int(int,int,int)> weightFunction, function<bool(int,int,int)> edgeCriteria) {
	ifstream fin;
	ofstream fout;
	
	fout.open(fileName);
	GraphImplementation outGraph(n);
	graphSetter(&outGraph, n, weightFunction, edgeCriteria);
	outGraph.serialize(fout, format);
	fout.close();
	
	fin.open(fileName);
	GraphImplementation inGraph(0); // graph is, in general, the incorrect size. Deserialize should fix this and an error should not be produced.
	inGraph.deserialize(fin, format);
	graphChecker(&inGraph, n, weightFunction, edgeCriteria);
	fin.close();
}

