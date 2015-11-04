#ifndef readPDBFile_h
#define readPDBFile_h

#include "AtomRecord.h"
#include <list>

void readPDBFile(	const char *file,
			std::list<AtomRecord> *atomList);

#endif

