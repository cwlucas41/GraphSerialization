//
//  Serializer.h
//  GraphSerialization
//
//  Created by Christopher Lucas on 4/25/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#ifndef __GraphSerialization__Serializer__
#define __GraphSerialization__Serializer__

#include <iostream>
class Graph;
using namespace std;
//#include "graph.h"

class Serializer {
	
public:
	virtual ~Serializer() {}
	virtual void serializeToFormat(Graph*, ostream&) = 0;
	virtual void deserializeToFormat(Graph*, istream&) = 0;
};

#endif /* defined(__GraphSerialization__Serializer__) */
