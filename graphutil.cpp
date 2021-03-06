// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// Functions for creating and printing graphs

#ifndef __graphUtil__
#define __graphUtil__

#define LINELEN 80

#include "graph.h"
#include <iostream>
#include <functional>
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


void Gprint(Graph* G) {
  int i, j;

  cout << "Number of vertices is " << G->n() << "\n";
  cout << "Number of edges is " << G->e() << "\n";

  cout << "Matrix is:\n";
  for (i=0; i<G->n(); i++) {
    for(j=0; j<G->n(); j++)
      cout << G->weight(i, j) << "\t";
    cout << "\n";
  }
}


char* getl(char* buffer, int n, FILE* fid) {
  char* ptr;
  ptr = fgets(buffer, n, fid);
  while ((ptr != NULL) && (buffer[0] == '#'))
    ptr = fgets(buffer, n, fid);
  return ptr;
}


// Create a graph from file fid
template <typename GType>
Graph* createGraph(FILE* fid) {
  char buffer[LINELEN+1]; // Line buffer for reading
  bool undirected;  // true if graph is undirected, false if directed
  int i;
  int v1, v2, dist;

  if (getl(buffer, LINELEN, fid) == NULL) // Unable to get number of vertices
{ cout << "Unable to read number of vertices\n";
    return NULL;
}

  Graph* G = new GType(atoi(buffer));

  if (getl(buffer, LINELEN, fid) == NULL) // Unable to get graph type
{ cout << "Unable to read graph type\n";
    return NULL ;
}
  if (buffer[0] == 'U')
    undirected = true;
  else if (buffer[0] == 'D')
    undirected = false;
  else {
    cout << "Bad graph type: |" << buffer << "|\n";
    return NULL;
  }

  // Read in edges
  while (getl(buffer, LINELEN, fid) != NULL) {
    v1 = atoi(buffer);
    i = 0;
    while (isdigit(buffer[i])) i++;
    while (buffer[i] == ' ') i++;
    v2 = atoi(&buffer[i]);
    while (isdigit(buffer[i])) i++;
    if (buffer[i] == ' ') { // There is a distance
      while (buffer[i] == ' ') i++;
      dist = atoi(&buffer[i]);
    }
    else dist = 1;
    G->setEdge(v1, v2, dist);
    if (undirected) // Put in edge in other direction
      G->setEdge(v2, v1, dist);
  }
  return G;
}

#endif
