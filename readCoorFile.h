#ifndef readCoorFile_h
#define readCoorFile_h

#include "AtomRecord.h"
#include <list>

void readCoorFile(	const char *file,
			std::list<AtomRecord> *atomList);

#endif
