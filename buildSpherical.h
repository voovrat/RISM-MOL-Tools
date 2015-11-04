#ifndef buildSpherical_h
#define buildSpherical_h

#include "UnaryFunction.h"
class Grid3DRISM;

void buildSpherical(	UnaryFunction<Real,Real> *fn,
			Grid3DRISM *grid,
			Real *data3D		// out
		);

#endif 
