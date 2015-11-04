#include "drawDeltaSphere4.h"

#include "Grid3DRISM.h"
#include <math.h>
#include "ArrayOperations.h"

void	drawDeltaSphere4(Real R,
			Real *data,
			Grid3DRISM *grid,
			Real dtheta,
			Real dphi)
{
	Real theta,phi;
	Real x,y,z;
	Integer offset;
	Real S;

	S=0;
	for(theta=0;theta<=M_PI;theta+=dtheta)
	{
		for(phi =0; phi<2*M_PI; phi+=dphi)
		{
			x = R * sin(theta) * cos(phi);
			y = R * sin(theta) * sin(phi);
			z = R * cos(theta);

			offset = getXYZOffset(	x,	//	Real x,
						y,	//	Real y,
						z,	//Real z,
						grid	//Grid3DRISM *grid
						);

			data[offset] += sin(theta);
			//S += sin(theta);
		}//phi		
	}//theta

	Real *ptr = data;
	Integer i;
	Integer N = grid->getNx() * grid->getNy() * grid->getNz();
	S=0;
	for(i=0;i<N;i++,ptr++)
		S+=*ptr;	

	mulArrayScalar<Real,Real>(	data,		//DataType *dst,
					1.0 / S / grid->getDRx() / grid->getDRy() / grid->getDRz(), //ScalarType scalar,
					grid->getNx() * grid->getNy() * grid->getNz()	//Integer N
				);

}
