#ifndef buildBigDistances_h
#define buildBigDistances_h

#include "Settings.h"
#include <list>
#include "AtomRecord.h"

void buildBigDistances(	std::list<std::list<AtomRecord> *> *atomListList,
			Integer BigN, // total number of sites in all molecules
			Real *BigDistances // out, pre-allocated BigN*BigN*sizeof(Real)
			);

#endif

