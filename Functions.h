//
//  Functions.h
//  GraphSerialization
//
//  Created by Christopher Lucas on 4/28/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#ifndef GraphSerialization_Functions_h
#define GraphSerialization_Functions_h

#include <cmath>
#include <functional>
#include <stdlib.h>
using namespace std;

function<int(int,int,int)> sumWeightFunction = [] (int x, int y, int size) {return x+y+size;};

function<int(int,int,int)> constantWeightFunction = [] (int x, int y, int size) {return size;};

function<int(int,int,int)> randomWeightFunction = [] (int x, int y, int size) {return rand();};


function<bool(int,int,int)> sparseEdgeCriteria = [] (int x, int y, int size) {
	int d = ceil(sqrt(size));
	return x%d == 0 && y%d == 0 && x!=y;
};

function<bool(int,int,int)> linearEdgeCriterion = [] (int x, int y, int size) {return ( x+1==y || y+1==x );};

function<bool(int,int,int)> completeEdgeCriteria = [] (int x, int y, int size) -> bool {return x!=y;};

#endif
