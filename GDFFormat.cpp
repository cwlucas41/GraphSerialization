//
//  GDFFormat.cpp
//  GraphSerialization
//
//  Created by Christopher Lucas on 4/25/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#include "GDFFormat.h"
#include "graph.h"

void GDFFormat::serialize(Graph *g, ostream &o){

	o<<"nodedef>name VARCHAR" << endl;
	for (int i = 0; i < g->n(); i++) {
		o<<"v"<<i<<endl;
	}
	o<<"edgedef>node1 VARCHAR,node2 VARCHAR,weight INT,directed"<<endl;
	for (int i = 0; i < g->n(); i++) {
		for (int j = g->first(i); j != g->n(); j = g->next(i, j)) {
			o<<"v"<<i<<",v"<<j<<","<<g->weight(i, j)<<",directed"<<endl;
		}
	}
}

void GDFFormat::deserialize(Graph *g, istream &i){
	string line;
	string vertex="v";
	string delimiter=",";
	getline(i,line); // node header
	
	getline(i, line); // prepare for while loop
	int	vertexCount = 0;
	while (line.find(",") == string::npos) {
		vertexCount++;
		getline(i, line); // catches edge header on last iteration
	}
	
	g->resize(vertexCount);
	
	while (getline(i,line)){
		int data[3];
		unsigned long vPos=0;
		unsigned long cmPos=0;
		for (int j=0;j<2;j++){
			vPos=line.find(vertex,vPos)+1;
			cmPos=line.find(delimiter,cmPos)+1;
			string stringVertex=line.substr(vPos,cmPos-vPos);
			data[j]=stoi(stringVertex);
		}
		string weight=line.substr(cmPos,line.find(delimiter,cmPos)-cmPos);
		data[2]=stoi(weight);
		g->setEdge(data[0],data[1],data[2]);
	}

}
