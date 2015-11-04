#ifndef buildSphericalK3_h
#define buildSphericalK3_h

#include "UnaryFunction.h"
#include <complex>
class Grid3DRISM;


// ResultType shuld be convertable to complex<Real>
// That's because one may have Real-valued function, which one want to represent as complex-valued

template<class ResultType>
void buildSphericalK3(	UnaryFunction<Real,ResultType> *fn,
			Grid3DRISM *grid,
			std::complex<Real> *data3D,		// out
			Real drDivider=7  	// x_step = dKx/drDivider, y_step = dKy/drDivider, z_step = dKz/drDivider
						// preferably, drDivider should be odd
	);

#endif
