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
	bool visited[g->n()];
	for (int i= 0;i<g->n();i++)
		visited[i] = false;
	visited[0]= true;
	// needs another block to iterate through all nodes? then end of iteration cycle?
	// block below, use MST to iterate through all the edges and their weights. Then put them into ostream
	for (int i= 0;i< g->n();i++){
		int u= g->first(i); // the first neighbor of i
		o<<"s"<<i<<","<<"s"<<u<<","<<g->weight(i,u)<<endl;
		while (int p = g->next(i,u)!= g->n()){ // if the next one is not equal to numVertex, that means i still has neighbour that is other than u
			if (visited[p] == true) continue;
			visited[p] = true;
			o<<"s"<<i<<","<<"s"<<p<<","<<g->weight(i,p)<<endl;
		}
		// end of iteration of edges
		
	}
	
}

void GDFFormat::deserialize(Graph *g, istream &i){
	string line;
	string vertex="v";
	string delimiter=",";
	
	for (int j=0; j < g->n()+2; j++)
		getline(i,line);
	
	while (getline(i,line)){
		int data[3]={0,0,0};
		unsigned long vPos=0;
		unsigned long cmPos=0;
		for (int j=0;j<2;j++){
			vPos=line.find(vertex,vPos)+1;
			cmPos=line.find(delimiter,cmPos)+1;
			string stringVertex=line.substr(vPos,cmPos-vPos);
			data[j]=stoi(stringVertex);
		}
		string weight=line.substr(cmPos,line.find("\n",0));
		data[2]=stoi(weight);
		g->setEdge(data[0],data[1],data[2]);
	}

}
