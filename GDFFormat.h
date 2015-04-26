//
//  GDFFormat.h
//  GraphSerialization
//
//  Created by Christopher Lucas on 4/25/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#ifndef __GraphSerialization__GDFFormat__
#define __GraphSerialization__GDFFormat__

#include <iostream>
#include "Serializer.h"

class GDFFormat: public Serializer {
	
public:
	void serialize(Graph*, ostream&);
	void deserialize(Graph*, istream&);
};

#endif /* defined(__GraphSerialization__GDFFormat__) */
