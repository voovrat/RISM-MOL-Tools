#include "buildSpherical4.h"

#include <math.h>

#include <stdlib.h>
#include <string.h>

#include "buildSpherical.h"

#include "Grid3DRISM.h"


// Peaks of RDFs are preserved....

void buildSpherical4 (
	UnaryFunction<Real,Real> *fn,
	Grid3DRISM *grid,
	Real *data,
	Integer divider
)
{

Integer Nx = grid->getNx();
Integer Ny = grid->getNy();
Integer Nz = grid->getNz();

Real dx = grid->getDRx();
Real dy = grid->getDRy();
Real dz = grid->getDRz();


if(dx<MIN_DR && dy<MIN_DR && dz<MIN_DR) // it may take too much time to refine the fine enough potentials...
{

 buildSpherical(	fn,		//UnaryFunction<Real,Real> *fn,
			grid,		//Grid3DRISM *grid,
			data		//Real *data3D		// out
		);
return;	
}


Real step_x = dx/divider;
Real step_y = dy/divider;
Real step_z = dz/divider;

Real halfCellX = divider/2*step_x;
Real halfCellY = divider/2*step_y;
Real halfCellZ = divider/2*step_z;
 

Real Xmax = (Nx/2)*dx;
Real Xmin = (-Nx/2+1)*dx; 

Real Ymax = (Ny/2)*dy ;
Real Ymin = (-Ny/2+1)*dy ;

Real Zmax = (Nz/2)*dz ;
Real Zmin = (-Nz/2 + 1)*dz;

Real dV = 1.0 / (divider * divider * divider);

Integer offset;
Real x,y,z;
Real x0,y0,z0;
//Real Mul,Mul2,Mul6,Mul12;

//potential->setZero();
memset(data,0,Nx*Ny*Nz*sizeof(Real));


//Real *S = (Real *)malloc( Nx*Ny*Nz*sizeof(Real) );

Real g_treshold = G_TRESHOLD;

Real Sum;
Real MaxG;
Integer inside;
Real *Gmap = (Real*)malloc((divider+2)*(divider+2)*(divider+2)*sizeof(Real));

//for( x0= Xmin; x0<=Xmax; x0+=dx )
//for( y0= Ymin; y0<=Ymax; y0+=dy )
//for( z0= Zmin; z0<=Zmax; z0+=dz )
offset=0;
GAMMA_FOR(grid)
{
//	offset = getXYZOffset(	x0,		//Real x,
//				y0,		//Real y,
//				z0,		//Real z,
//				grid		//Grid3DRISM *grid
//				);
	 	
//	if(offset<0) continue;

	Real g;
	Real MinR = 10000;

	x0 = GAMMA_FOR_X;
	y0 = GAMMA_FOR_Y;
	z0 = GAMMA_FOR_Z;

	Real R = sqrt(x0*x0 + y0*y0 + z0*z0);
//	Real R = GAMMA_FOR_R;

	g= (*fn)(R);

	if(R> COARSE_POT_CUT || g<g_treshold ) 
	{	data[offset]=g;
		offset++;
		continue;
	}
	

	int i,j,k;
	Sum=0;
	MaxG =0;
	inside = 0;
//	Real loc_dx,loc_dy,loc_dz;

	// we should not count one ma
	for(x=x0-halfCellX-step_x,i=0; i<divider+2;  x+=step_x,i++)
	for(y=y0-halfCellY-step_y,j=0; j<divider+2; y+=step_y,j++)
	for(z=z0-halfCellZ-step_z,k=0; k<divider+2; z+=step_z,k++)		
	{

	Real R = sqrt(x*x + y*y + z*z );

	g=(*fn)(R);


	Gmap[ (i*(divider+2) + j)*(divider+2) + k ] = g;

	inside =(i>0) && (i<divider+1) && 
		(j>0) && (j<divider+1) && 
		(k>0) && (k<divider+1);
	

	if(inside) Sum+=g;
	}//sub xyz


	Integer divider2 = (divider+2)*(divider+2);
	Integer LocMaxCount=0;
	Real LocMaxG =0;
	Integer loc_offset;
	Integer border = 2;
	for(i=1+border; i<divider+1-border; i++)
	for(j=1+border; j<divider+1-border; j++)
	for(k=1+border; k<divider+1-border; k++)
	{
		loc_offset = (i*(divider+2) + j)*(divider+2) + k;

		if( 	(Gmap[loc_offset]>Gmap[loc_offset+divider2] && // in x direction
			Gmap[loc_offset]>Gmap[loc_offset-divider2] ) 
			|| 
			(Gmap[loc_offset]>Gmap[loc_offset+divider+2] && // in y direction
			Gmap[loc_offset]>Gmap[loc_offset-divider-2] ) 
			||
			(Gmap[loc_offset]>Gmap[loc_offset+1] && // in z direction
			 Gmap[loc_offset]>Gmap[loc_offset-1] ) 
		)
		{
			LocMaxCount++;
			LocMaxG +=Gmap[loc_offset];
		}


	}


	if(LocMaxCount>0) data[offset]=LocMaxG/LocMaxCount;
	else data[offset]=Sum/(divider*divider*divider);
	

offset ++;
}//xyz
END_GAMMA_FOR


free(Gmap);

}
