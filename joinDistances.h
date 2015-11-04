#ifndef joinDistances_h
#define joinDistances_h

#include "Settings.h"
#include <list>
#include "AtomRecord.h"


void joinDistances(	std::list<AtomRecord> *atomlist,
			Real *distances,
			Integer Nsites,
			Integer *Joins
		);

#endif

