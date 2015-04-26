//
//  DOTFormat.h
//  GraphSerialization
//
//  Created by Christopher Lucas on 4/25/15.
//  Copyright (c) 2015 CWL. All rights reserved.
//

#ifndef __GraphSerialization__DOTFormat__
#define __GraphSerialization__DOTFormat__

#include <iostream>
#include "Serializer.h"

class DOTFormat: public Serializer {
	
public:
	void serializeToFormat(Graph*, ostream&);
	void deserializeToFormat(Graph*, istream&);
};

#endif /* defined(__GraphSerialization__DOTFormat__) */
