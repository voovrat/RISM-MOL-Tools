#include "buildSphericalK.h"

#include "UnaryFunction.h"
#include "Grid3DRISM.h"

#include <complex>

template<class ResultType>
void buildSphericalK(	UnaryFunction<Real,ResultType> *fn,
			Grid3DRISM *grid,
			std::complex<Real> *data3D		// out
		)
{
	std::complex<Real> *ptr = data3D;

	KGAMMA_FOR(grid)
	{
		Real kr = KGAMMA_FOR_KR;
		*ptr += (*fn)(kr);
		ptr++;
	}
	END_KGAMMA_FOR   
}
