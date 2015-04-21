// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// Include this file to access Graph representation implemented using an
// Adjacency Matrix.

#ifndef __Graphm__
#define __Graphm__

#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <string>

// Used by the mark array
#define UNVISITED 0
#define VISITED 1

#include "graph.h"

// Implementation for the adjacency matrix representation
class Graphm : public Graph {
private:
  int numVertex, numEdge; // Store number of vertices, edges
  int **matrix;           // Pointer to adjacency matrix
  int *mark;              // Pointer to mark array
public:
  Graphm(int numVert)     // Constructor
    { Init(numVert); }

  ~Graphm() {       // Destructor
    delete [] mark; // Return dynamically allocated memory
    for (int i=0; i<numVertex; i++)
      delete [] matrix[i];
    delete [] matrix;
  }

  void Init(int n) { // Initialize the graph
    int i;
    numVertex = n;
    numEdge = 0;
    mark = new int[n];     // Initialize mark array
    for (i=0; i<numVertex; i++)
      mark[i] = UNVISITED;
    matrix = (int**) new int*[numVertex]; // Make matrix
    for (i=0; i<numVertex; i++)
      matrix[i] = new int[numVertex];
    for (i=0; i< numVertex; i++) // Initialize to 0 weights
      for (int j=0; j<numVertex; j++)
        matrix[i][j] = 0;
  }

  int n() { return numVertex; } // Number of vertices
  int e() { return numEdge; }   // Number of edges

  // Return first neighbor of "v"
  int first(int v) {
    for (int i=0; i<numVertex; i++)
      if (matrix[v][i] != 0) return i;
    return numVertex;           // Return n if none
  }

  // Return v's next neighbor after w
  int next(int v, int w) {
    for(int i=w+1; i<numVertex; i++)
      if (matrix[v][i] != 0)
        return i;
    return numVertex;           // Return n if none
  }

  // Set edge (v1, v2) to "wt"
  void setEdge(int v1, int v2, int wt) {
    Assert(wt>0, "Illegal weight value");
    if (matrix[v1][v2] == 0) numEdge++;
    matrix[v1][v2] = wt;
  }

  void delEdge(int v1, int v2) { // Delete edge (v1, v2)
    if (matrix[v1][v2] != 0) numEdge--;
    matrix[v1][v2] = 0;
  }

  bool isEdge(int i, int j) // Is (i, j) an edge?
  { return matrix[i][j] != 0; }

  int weight(int v1, int v2) { return matrix[v1][v2]; }
  int getMark(int v) { return mark[v]; }
  void setMark(int v, int val) { mark[v] = val; }
	
	void serialize(ostream& o) /*const*/{
		o<<"digraph serializedGraph {"<<endl;
		for (int i=0;i<n();i++){
			for (int j = first(i); j != n(); j = next(i, j)) {
					o<<"\tv"<<i<<" -> "<<"v"<<j<<" [label="<<weight(i, j)<<"];"<<endl;
			}
		}
	o<<"}"<<endl;
  }

	
	void deserialize(istream& i){
		string line;
		string vertexConvention = "v";
		string delimiter = " ";
		getline(i, line); // header
		while (getline(i,line) && line.find("}") == string::npos) {
			unsigned long vPos = 0;
			unsigned long spPos = 0;
			int data[3] = {0,0};
			for (int i = 0; i < 2; i++) {
				vPos = line.find(vertexConvention,vPos)+1;//从0开始找v位置，vPos=位置+1 => e.g. v1的1的位置
				spPos = line.find(delimiter,spPos);//找空格的位置
				string stringVertex = line.substr(vPos, spPos-vPos);//substring [vPos,spPos) v1的1
				data[i] = stoi(stringVertex);//string转换成int e.g. data=[1]
			}
			unsigned long eqPos = line.find("=")+1;
			string weight = line.substr(eqPos,line.find("]")-eqPos);
			data[2] = stoi(weight);
			setEdge(data[0], data[1], data[2]);
		}
	}
	
	void GDFdeserialize(istream& i){
		string line;
		string vertex="v";
		string delimiter=",";
		for (int j=0;j<5;j++)
			getline(i,line);
		while (getline(i,line)){
			unsigned long vPos=0;
			unsigned long cmPos=0;
			int data[3];
			for (int j=0;j<2;j++){
				vPos=line.find(vertex,vPos)+1;
				cmPos=line.find(delimiter,cmPos;
				string stringVertex=line.substr(vPos,cmPos-vPos);
				data[i]=stoi(stringVertex);
			}
			string weight=line.substr(cmPos+1,-1);
			data[2]=stoi(weight);
			setEdge(data[0],data[1],data[2]);
		}
	}
	
};

#include "graphutil.cpp"

#endif
