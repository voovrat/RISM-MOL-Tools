#include "buildSpherical.h"

#include "Grid3DRISM.h"
#include "UnaryFunction.h"

void buildSpherical(	UnaryFunction<Real,Real> *fn,
			Grid3DRISM *grid,
			Real *data3D		// out
		)
{
	Real *ptr = data3D;

	GAMMA_FOR(grid)
	{
		Real r = GAMMA_FOR_R;
		*ptr  = (*fn)(r);
		ptr++;
	}
	END_GAMMA_FOR   
}
