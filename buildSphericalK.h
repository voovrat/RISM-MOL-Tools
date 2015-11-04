#ifndef buildSphericalK_h
#define buildSphericalK_h

class Solution3DRISMK;

#include "UnaryFunction.h"
#include <complex>

// ResultType shuld be convertable to complex<Real>
// That's because one may have Real-valued function, which one want to represent as complex-valued

class Grid3DRISM;

template<class ResultType>
void buildSphericalK(	UnaryFunction<Real,ResultType> *fn,
			Grid3DRISM *grid,
			std::complex<Real> *data3D		// out
		);


#endif 
