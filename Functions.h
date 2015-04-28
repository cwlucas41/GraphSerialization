//
//  Functions.h
//  GraphSerialization
//
//  Created by Christopher Lucas on 4/27/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#ifndef GraphSerialization_Functions_h
#define GraphSerialization_Functions_h
#include <cmath>
#include <functional>
using namespace std;

function<int(int,int,int)> weightFunction = [] (int x, int y, int size) {return x+y+size;};

function<bool(int,int,int)> sparseEdgeCriteria = [] (int x, int y, int size) {
	int d = ceil(sqrt(size));
	return x%d == 0 && y%d == 0;
};

function<bool(int,int,int)> denseEdgeCriteria = [] (int x, int y, int size) -> bool {return true;};

#endif
