// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// Graph abstract class. This ADT assumes that the number
// of vertices is fixed when the graph is created.

#ifndef __Graph__
#define __Graph__

#include <iostream>
#include "string"
using namespace std;
class Graph {
private:
  void operator =(const Graph&) {}     // Protect assignment
  Graph(const Graph&) {}         // Protect copy constructor

public:
  Graph() {}          // Default constructor
  virtual ~Graph() {} // Base destructor

  // Initialize a graph of n vertices
  virtual void Init(int n) =0;

  // Return: the number of vertices and edges
  virtual int n() =0;
  virtual int e() =0;

  // Return v's first neighbor
  virtual int first(int v) =0;

 // Return v's next neighbor
  virtual int next(int v, int w) =0;

  // Set the weight for an edge
  // i, j: The vertices
  // wgt: Edge weight
  virtual void setEdge(int v1, int v2, int wght) =0;

  // Delete an edge
  // i, j: The vertices
  virtual void delEdge(int v1, int v2) =0;

  // Determine if an edge is in the graph
  // i, j: The vertices
  // Return: true if edge i,j has non-zero weight
  virtual bool isEdge(int i, int j) =0;

  // Return an edge's weight
  // i, j: The vertices
  // Return: The weight of edge i,j, or zero
  virtual int weight(int v1, int v2) =0;

  // Get and Set the mark value for a vertex
  // v: The vertex
  // val: The value to set
  virtual int getMark(int v) =0;
  virtual void setMark(int v, int val) =0;
	
	virtual void resize(int n){
		this->~Graph();
		this->Init(n);
	}
	
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
			for (int j = 0; j < 2; j++) {
				vPos = line.find(vertexConvention,vPos)+1;
				spPos = line.find(delimiter,spPos);
				string stringVertex = line.substr(vPos, spPos-vPos);
				data[j] = stoi(stringVertex);
			}
			unsigned long eqPos = line.find("=")+1;
			string weight = line.substr(eqPos,line.find("]")-eqPos);
			data[2] = stoi(weight);
			setEdge(data[0], data[1], data[2]);
		}
	}
	
};

#endif