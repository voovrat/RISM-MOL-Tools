#include "Settings.h"
#include "Grid3DRISM.h"

Integer isLocalMax(	Real *data,	
			Grid3DRISM *grid,
			Real x0,
			Real y0,
			Real z0,
			Real radius )
{

Integer offset;
Real G0;

offset =  getXYZOffset(	x0,	//Real x,
			y0,	//Real y,
			z0,	//Real z,
			grid	//Grid3DRISM *grid
		);

if(offset<0) return 0;

G0 = data[offset];

Real x,y,z;
Real dx = grid->getDRx();
Real dy = grid->getDRy();
Real dz = grid->getDRz();

Real DX,DY,DZ;
Real R2 = radius*radius;

for(x=x0-radius; x<=x0+radius; x+=dx)
for(y=y0-radius; y<=y0+radius; y+=dy)
for(z=z0-radius; z<=z0+radius; z+=dz)
{
	DX = x-x0;
	DY = y-y0;
	DZ = z-z0;
	
	if( DX*DX + DY*DY + DZ*DZ > R2) continue;
	
	offset =  getXYZOffset(	x,	//Real x,
				y,	//Real y,
				z,	//Real z,
				grid	//Grid3DRISM *grid
				);

	if(offset<0) continue;

	if(data[offset]>G0) return 0;

}//for x,y,z

return 1;

}
