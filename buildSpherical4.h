#ifndef buildSpherical4_h
#define buildSpherical4_h
//#include <math.h>

//#include <stdlib.h>
//#include <string.h>

//#include "buildPotential.h"

#include "UnaryFunction.h"
class Grid3DRISM;

#include "Settings.h"


// peaks of RDFs are preserved

void buildSpherical4 (
	UnaryFunction<Real,Real> *fn,
	Grid3DRISM *grid,
	Real *data,
	Integer divider = AVERAGING_DIVIDER
);

#endif
