//
//  DOTFormat.cpp
//  GraphSerialization
//
//  Created by Christopher Lucas on 4/25/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#include "DOTFormat.h"
#include "graph.h"

void DOTFormat::serializeToFormat(Graph* g, ostream& o) {
	o<<"digraph serializedGraph {"<<endl;
	for (int i=0;i < g->n();i++){
		o<<"v"<<i<<endl;
	}
	for (int i=0;i < g->n();i++){
		for (int j = g->first(i); j != g->n(); j = g->next(i, j)) {
			o<<"v"<<i<<" -> "<<"v"<<j<<" [label="<<g->weight(i, j)<<"];"<<endl;
		}
	}
	o<<"}"<<endl;
}

void DOTFormat::deserializeToFormat(Graph* g, istream& i) {
	string line;
	string vertexConvention = "v";
	string delimiter = " ";
	getline(i, line); // header
	
	getline(i, line); // prepare for while loop
	int	vertexCount = 0;
	while (line.find("->") == string::npos) {
		vertexCount++;
		getline(i, line);
	}
	
	g->resize(vertexCount);
	
	while (line.find("}") == string::npos) {
		unsigned long vPos = 0;
		unsigned long spPos = 0;
		int data[3];
		for (int j = 0; j < 2; j++) {
			vPos = line.find(vertexConvention,vPos)+1;
			spPos = line.find(delimiter,spPos);
			string stringVertex = line.substr(vPos, spPos-vPos);
			data[j] = stoi(stringVertex);
		}
		unsigned long eqPos = line.find("=")+1;
		string weight = line.substr(eqPos,line.find("]")-eqPos);
		data[2] = stoi(weight);
		g->setEdge(data[0], data[1], data[2]);
		getline(i,line);
	}
}
