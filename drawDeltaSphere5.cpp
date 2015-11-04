#include "drawDeltaSphere5.h"

#include "Grid3DRISM.h"
#include <math.h>
#include "ArrayOperations.h"

void	drawDeltaSphere5(Real R,
			Real *data,
			Grid3DRISM *grid,
			Real dtheta,
			Real dphi)
{
	Real theta,phi;
	Real x,y,z;
	Integer offset;
	Real S;
//	Real x0,x1,y0,y1,z0,z1;
	Real dx,dy,dz;
	Real x_node,y_node,z_node;

	dx = grid->getDRx();
	dy = grid->getDRy();
	dz = grid->getDRz();

	S=0;
	for(theta=0;theta<=M_PI;theta+=dtheta)
	{
		for(phi =0; phi<2*M_PI; phi+=dphi)
		{
			x = R * sin(theta) * cos(phi);
			y = R * sin(theta) * sin(phi);
			z = R * cos(theta);
			
			x_node = (x>0) ? dx*(Integer)(x/dx+0.5) : dx*(Integer)(x/dx-0.5);
			y_node = (y>0) ? dy*(Integer)(y/dy+0.5) : dy*(Integer)(y/dy-0.5);
			z_node = (z>0) ? dz*(Integer)(z/dz+0.5) : dz*(Integer)(z/dz-0.5);

			
  	
			offset = getXYZOffset(	x,	//	Real x,
						y,	//	Real y,
						z,	//Real z,
						grid	//Grid3DRISM *grid
						);

			data[offset] += sin(theta) *	(1-fabs(x-x_node)/dx) * (1-fabs(y-y_node)/dy) * (1-fabs(z-z_node)/dz);
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
					1.0/S/grid->getDRx() / grid->getDRy() / grid->getDRz(),		//ScalarType scalar,
					grid->getNx() * grid->getNy() * grid->getNz()	//Integer N
				);

}
