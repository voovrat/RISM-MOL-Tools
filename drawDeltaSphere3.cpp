#include "drawDeltaSphere3.h"

#include "Grid3DRISM.h"
#include "ArrayOperations.h"
#include <math.h>

void	drawDeltaSphere3(Real R,
			Real *data,
			Grid3DRISM *grid,
			Integer RADIUS_FACTOR)
{
Integer S =0;

Real *ptr = data;
Real eps = grid->getDRx()/2;
Real dR = grid->getDRx();

Integer X = ( R / dR < RADIUS_FACTOR)&& (R>0);

GAMMA_FOR(grid)
{

	if( X && (GAMMA_FOR_R>R && fabs(GAMMA_FOR_R - R)<dR) ||
	    !X && fabs(GAMMA_FOR_R - R)<eps 
	)
	{
		*ptr = 1;
		S++;
	}
	else
	{
		*ptr = 0;
	}	

	ptr++;
}
END_GAMMA_FOR

Integer N = grid->getNx() * grid->getNy() * grid->getNz();


Real S2 = (Real)S * grid->getDRx() * grid->getDRy() * grid->getDRz();

divArrayScalar<Real,Real>
		(	data, 	//DataType *dst,
			S2,	//ScalarType scalar,
			N	//Integer N
			);

}
