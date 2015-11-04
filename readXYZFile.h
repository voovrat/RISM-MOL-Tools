#ifndef readXYZFile_h
#define readXYZFile_h

#include "AtomRecord.h"
#include <list>

void readXYZFile(	const char *file,
			std::list<AtomRecord> *atomList);

#endif

