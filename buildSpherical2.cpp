#include "buildSpherical2.h"

#include "UnaryFunction.h"
#include "Grid3DRISM.h"

void buildSpherical2(	UnaryFunction<Real,Real> *fn,
			Grid3DRISM *grid,
			Real *data3D,		// out
			Integer divider 
		)
{

Integer Nx = grid->getNx();
Integer Ny = grid->getNy();
Integer Nz = grid->getNz();

Real dx = grid->getDRx();
Real dy = grid->getDRy();
Real dz = grid->getDRz();

Real step_x = dx/divider;
Real step_y = dy/divider;
Real step_z = dz/divider;

Real Xmax = (Nx/2)*dx + divider/2*step_x;
Real Xmin = (-Nx/2+1)*dx - divider/2*step_x;

Real Ymax = (Ny/2)*dy + divider/2*step_y;
Real Ymin = (-Ny/2+1)*dy - divider/2*step_y;

Real Zmax = (Nz/2)*dz + divider/2*step_z;
Real Zmin = (-Nz/2 + 1)*dz - divider/2*step_z;

Real dV = 1.0 / (divider*divider*divider);

Integer offset;
Real x,y,z;

memset(data3D,0,Nx*Ny*Nz*sizeof(Real));
	
for( x= Xmin; x<Xmax; x+=step_x )
for( y= Ymin; y<Ymax; y+=step_y )
for( z= Zmin; z<Zmax; z+=step_z )
{
	offset = getXYZOffset(	x,		//Real x,
				y,		//Real y,
				z,		//Real z,
				grid		//Grid3DRISM *grid
				);
	 
//	if(offset==0)
//		printf("%ld\n",offset);
	
	if(offset<0) continue;

	
	Real R = sqrt(x*x + y*y + z*z);


	data3D[offset] += (*fn)(R) * dV ;

}//xyz

}

