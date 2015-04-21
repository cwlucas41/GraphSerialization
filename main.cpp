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

void graphSumSetter(Graph* g, int n){
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			int weight = i+j;
			if (weight > 0 && i!=j) {
				g->setEdge(i, j, weight);
			}
		}
	}
}

void graphSumChecker(Graph* g, int n){
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			int weight = i+j;
			if (weight > 0 && i!=j) {
				checkEdge(g, i, j, weight);
			}
		}
	}
}

int main(int argc, const char * argv[]) {
	
	int size = 125;
	
	// Dot format serialize adj list graph
	ofstream foutl;
	foutl.open("graphl.dot");
	Graphl outGraphl(size);
	graphSumSetter(&outGraphl,size);
	outGraphl.serialize(foutl);
	foutl.close();
	
	//Dot format deserialize adj list graph
	ifstream finl;
	finl.open("graphl.dot");
	Graphl inGraphl(size);
	inGraphl.deserialize(finl);
	graphSumChecker(&inGraphl, size);
	finl.close();
	
	//Dot format serializd mat graph
	ofstream foutm;
	foutm.open("graphm.dot");
	Graphm outGraphm(size);
	graphSumSetter(&outGraphm, size);
	outGraphm.serialize(foutm);
	foutm.close();
	
	//Dot format deserialize mat graph
	ifstream finm;
	finm.open("graphm.dot");
	Graphm inGraphm(size);
	inGraphm.deserialize(finm);
	graphSumChecker(&inGraphm, size);
	finm.close();
	
	return 0;
}
