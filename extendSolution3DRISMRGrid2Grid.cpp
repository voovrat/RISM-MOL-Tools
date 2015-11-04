#include "Settings.h"

#include "Solution3DRISMR.h"
#include "Grid3DRISM.h"
#include "extendSolution3DRISMRGrid2Grid.h"

void extendSolution3DRISMRGrid2Grid(	Solution3DRISMR *src,
					Solution3DRISMR *dst
				)
{

Integer Nsites = src->getNumberOfSites();
Grid3DRISM *srcGrid = (Grid3DRISM *)src->getGrid();
Grid3DRISM *dstGrid = (Grid3DRISM *)dst->getGrid();

Integer site;
for(site = 0; site<Nsites; site++)
{
	GAMMA_FOR_SOLUTION(src,site)
	{
		Real x = GAMMA_FOR_X;
		Real y = GAMMA_FOR_Y;
		Real z = GAMMA_FOR_Z;

		Integer offset;
		offset = getXYZOffset(	x,	//Real x,
					y,	//Real y,
					z,	//Real z,
					dstGrid	//Grid3DRISM *grid
				);
		Real data = GAMMA_FOR_DATA;

 		dst->getGamma()[site][offset] = data;
		


	}
	END_GAMMA_FOR_SOLUTION

}

}
