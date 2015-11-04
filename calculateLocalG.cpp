#include "calculateLocalG.h"

#include <math.h>

#include "Settings.h"
#include "Grid3DRISM.h"


// calculates product of g's in near x0,y0,z0


Real calculateLocalG( 	Real **g_index, // array of g functions in real (see N )	
			Grid3DRISM * grid, 	
			Real *coors,	// coordinates of the solvent molecule 
			int Nsites, // number of atoms in solvent (NO Multiple nsites!! all multiplicities=1, (eg for water N=3))
			Real x0,
			Real y0,
			Real z0
			)
{
Real *XYZ = coors;
Real G = 1;
Real x,y,z;
Integer offset;
Integer site;
for(site=0;site<Nsites; site++, XYZ += 3)
{
	x = x0 + XYZ[0];
	y = y0 + XYZ[1];
	z = z0 + XYZ[2];
	
	offset = getXYZOffset(	x,	//Real x,
				y,	//Real y,
				z,	//Real z,
				grid	//Grid3DRISM *grid
			);

	G *= g_index[site][offset];

}//for site


if(G<1e-18) G = 1e-18;

return exp((double)1.0/Nsites * log(G));  // G^(1/Nsites)

} 

