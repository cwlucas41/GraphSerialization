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
using namespace std;

int main(int argc, const char * argv[]) {

	ofstream fout;
	fout.open("graph2.dot");
	
	Graphm outGraph(8);
	outGraph.setEdge(1, 2, 1);
	outGraph.setEdge(7, 4, 4);
	outGraph.setEdge(4, 7, 2);
	outGraph.serialize(fout);
	fout.close();
	
	ifstream fin;
	fin.open("graph2.dot");
	Graphm inGraph(8);
	inGraph.deserialize(fin);
	inGraph.isEdge(1, 2);
	inGraph.isEdge(7, 4);
	inGraph.isEdge(4, 7);
	fin.close();
	
	return 0;
}
