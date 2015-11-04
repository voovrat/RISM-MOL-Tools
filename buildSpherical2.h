#ifndef buildSpherical2_h
#define buildSpherical2_h

#include "UnaryFunction.h"
class Grid3DRISM;

void buildSpherical2(	UnaryFunction<Real,Real> *fn,
			Grid3DRISM *grid,
			Real *data3D,		// out
			Integer divider = AVERAGING_DIVIDER
		);

#endif 
