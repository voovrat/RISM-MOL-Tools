#ifndef calculateCompressibility_h
#define calculateCompressibility_h

#include "Settings.h"

// Warning! Function work for one component solutions
// Result - in rdf units (Bohr^3) 
// Kaclulates kbT * kappa! 


// kappa = 1/denity + 4 pi int (g - 1)r^2 dr

class TabFunction;

Real calculateCompressibility(	TabFunction *rdf,
				Real density);




#endif
