#include "restrictSolution3DRISMR.h"

#include "Solution3DRISMR.h"
#include "Grid3DRISM.h"


void restrictSolution3DRISMR(	Solution *fine0,
				Solution *coarse0
				)
{

Solution3DRISMR *fine = dynamic_cast<Solution3DRISMR *>(fine0);
Solution3DRISMR *coarse = dynamic_cast<Solution3DRISMR *>(coarse0);

Integer numSites = fine->getNumberOfSites();

Integer site;
Integer x,y,z;

Grid3DRISM *coarseGrid = (Grid3DRISM *)coarse->getGrid();

Integer Nx = coarseGrid->getNx();
Integer Ny = coarseGrid->getNy();
Integer Nz = coarseGrid->getNz();

Integer stride_y = 2*Nz;
Integer stride_x = (2*Ny)*(2*Nz);

for(site = 0; site<numSites; site++)
{
Real *src = fine->getGamma()[site];
Real *dst = coarse->getGamma()[site];

	for(x=0;x<Nx;x++)
	{
		for(y=0;y<Ny;y++)
		{
			for(z=0;z<Nz;z++)
			{
				*dst = *src;
				//*dst = ( *src + *(src+1) + 
				//	 *(src+stride_y) + *(src+stride_y+1) +
				//	 *(src+stride_x) + *(src+stride_x+1) + 
				//	 *(src+stride_x+stride_y) + *(src+stride_x+stride_y+1)
				//	) / 8;
	
				src+=2; // omit one z
				dst++; // next z
			}//for z
			src+=2*Nz; // omit one y
		}// for y
		src+=(2*Ny)*(2*Nz); // omit one x
	}//for x
}// site


}

