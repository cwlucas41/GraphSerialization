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

	ifstream fin;
	fin.open("graph1.dot");
	
	Graphm myGraph(8);
	myGraph.deserialize(fin);
	
	return 0;
}
