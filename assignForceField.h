#ifndef assignForceField_h
#define assignForceField_h

// assigns a forceField to the molecule...
// Force field is a list of patterns..

class AtomPatternArray;
#include <list>

void assignForceField( 	AtomPatternArray *molecule,
			std::list<AtomPatternArray *> *forceField
			);

#endif
