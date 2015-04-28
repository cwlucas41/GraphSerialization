//
//  graphutil.h
//  GraphSerialization
//
//  Created by Christopher Lucas on 4/27/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#ifndef GraphSerialization_graphutil_h
#define GraphSerialization_graphutil_h



void Gprint(Graph* G);

void graphChecker(Graph* g, int n, function<int(int, int,int)> w, function<bool(int, int,int)> acc);

void graphSetter(Graph* g, int n, function<int(int, int,int)> w, function<bool(int, int,int)> acc);

void checkEdge(Graph* g, int v1, int v2, int weight);



#endif
