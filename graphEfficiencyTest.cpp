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
#include <stdlib.h>
#include <utility>
#include <fstream>
using namespace std;

template<typename GraphType>
pair<double, double> averageTimesOfDijkstraForGraphSize(int size, int toCheck, function<int(int,int,int)> weightFunction, function<bool(int,int,int)> acceptanceFunction);

void testDijkstra(string fileName, int start, int max, int step, int verteciesToConsider, function<int(int,int,int)> weightFunction, function<bool(int,int,int)> acceptanceFunction);

template<typename T>
T averageOfArray(T* arr, int n);

int main(int argc, const char * argv[]) {
	
	int startSize = 1000;
	int maxSize = 35000;
	int stepSize = 1000;
	int verticiesToAverage = 10;
	
	testDijkstra("randomSparse.csv", startSize, maxSize, stepSize, verticiesToAverage, randomWeightFunction, sparseEdgeCriteria);
	testDijkstra("randomLinear.csv", startSize, maxSize, stepSize, verticiesToAverage, randomWeightFunction, linearEdgeCriterion);
	testDijkstra("randomComplete.csv", startSize, maxSize, stepSize, 2, randomWeightFunction, completeEdgeCriteria);
	
	return 0;
}

void testDijkstra(string fileName, int start, int max, int step, int verteciesToConsider, function<int(int,int,int)> weightFunction, function<bool(int,int,int)> acceptanceFunction) {
	ofstream fout;
	fout.open(fileName);
	fout<<"verticies, Graphl, PQ and Graphl, Graphm, PQ and Graphm, speedup for PQ and Graphl, speedup for PQ and Graphm"<<endl;
	for (int size = start; size <= max; size += step) {
		pair<double, double> listResults = averageTimesOfDijkstraForGraphSize<Graphl>(size, verteciesToConsider, weightFunction, acceptanceFunction);
		pair<double, double> matResults = averageTimesOfDijkstraForGraphSize<Graphm>(size, verteciesToConsider, weightFunction, acceptanceFunction);
		fout<<size<<", "<<get<0>(listResults)<<", "<<get<1>(listResults)<<", "<<get<0>(matResults)<<", "<<get<1>(matResults)<<", "<<get<0>(listResults)/get<1>(listResults)<<", "<<get<0>(matResults)/get<1>(matResults)<<endl;
		}
	fout.close();
}

template<typename GraphType>
pair<double, double> averageTimesOfDijkstraForGraphSize(int size, int toCheck, function<int(int,int,int)> weightFunction, function<bool(int,int,int)> acceptanceFunction){
	int dijkList[size];
	int optimizedDijkList[size];
	int vertexToCheck = 0;
	double results[toCheck];
	double optimizedResults[toCheck];
	pair<double, double> toReturn;

	GraphType G(size);
	graphSetter(&G, size, weightFunction, acceptanceFunction);
	for (int count = 0; count < toCheck; count++) {
		
		vertexToCheck = rand()%size;
		
		for (int i = 0; i < size; i++) {
			dijkList[i] = INFINITY;
			optimizedDijkList[i] = INFINITY;
		}
		dijkList[vertexToCheck]=0;
		optimizedDijkList[vertexToCheck]=0;
		
		Settime();
		Dijkstra(&G, dijkList, vertexToCheck);
		results[count] = Gettime();
		
		Settime();
		DijkstraImproved(&G, optimizedDijkList, vertexToCheck);
		optimizedResults[count] = Gettime();
	}
	
	double average = averageOfArray<double>(results, toCheck);
	double optimizedAverage = averageOfArray<double>(optimizedResults, toCheck);
	toReturn = pair<double, double>(average, optimizedAverage);
	
	return toReturn;
}

template<typename T>
T averageOfArray(T* arr, int n){
	T total = 0;
	for (int i = 0; i < n; i++) {
		total += *(arr+i);
	}
	return total /(T) n;
}