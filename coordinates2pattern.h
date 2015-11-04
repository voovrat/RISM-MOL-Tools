#ifndef coordinates2pattern_h
#define coordinates2pattern_h

#include "Settings.h"

#include "AtomRecord.h"
class AtomPatternArray;

#include <list>
#include <string>
#include <map>

void coordinates2pattern(	std::list<AtomRecord> *records,
				AtomPatternArray *patternArray,
				std::map<std::string,Real> *sigmas);


#endif
