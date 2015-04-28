//
//  graphEfficiencyTest.cpp
//  GraphSerialization
//
//  Created by Christopher Lucas on 4/27/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#include <stdio.h>
#include "Functions.h"
#include "grmat.h"
#include "grlist.h"
#include "graphutil.h"
#include "book.h"
#include "dijkstra.h"


int main(int argc, const char * argv[]) {
	
	int size = 5000;
	int dijkList[size];
	for (int vertexToCheck = 0; vertexToCheck < size; vertexToCheck++) {
		Graphl G(size);

		for (int i = 0; i < size; i++) {
		dijkList[i] = INFINITY;
		}
		dijkList[vertexToCheck]=0;
	
		Settime();
		Dijkstra(&G, dijkList, vertexToCheck);
		cout << Gettime() << endl;
	}
	
	Graphl listGraph(size);
	Graphm matGraph(size);
	cout<<"size of list implementation: "<<sizeof(listGraph)<<endl<<"size of matrix implementation: "<<sizeof(matGraph)<<endl;
	
	
	return 0;
}