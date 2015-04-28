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

int main(int argc, const char * argv[]) {
	
	DOTFormat dotFormat;
	GDFFormat gdfFormat;
	int size = 10;

	
	Graphm test(0);
	test.resize(size);
	if (size != test.n()) {
		cout << "Resize failed" << endl;
	}
	
	testLinearization<Graphl>(size, "l.dot", &dotFormat, sumWeightFunction, sparseEdgeCriteria);
	testLinearization<Graphm>(size, "m.dot", &dotFormat, sumWeightFunction, sparseEdgeCriteria);
	testLinearization<Graphl>(size, "l.gdf", &gdfFormat, sumWeightFunction, sparseEdgeCriteria);
	testLinearization<Graphm>(size, "m.gdf", &gdfFormat, sumWeightFunction, sparseEdgeCriteria);
	
	return 0;
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

