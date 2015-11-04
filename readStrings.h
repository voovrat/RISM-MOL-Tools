#ifndef readStrings_h
#define readStrings_h

#include <stdio.h>
#include <list>
#include <string>

void readStrings(	FILE *f,
			std::list<std::string> *strings,
			int trimStrings=1,	// remove spaces from begin/end
			int removeEmptyStrings=1 //boolean
		);

#endif

