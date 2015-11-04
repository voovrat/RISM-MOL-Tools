#include "extendSolution3DRISMR.h"

#include "Grid3DRISM.h"
#include "Solution3DRISMR.h"

void  extendSolution3DRISMR(	Solution *in0,
				Solution *out0
				)
{
Solution3DRISMR *in = dynamic_cast<Solution3DRISMR *>(in0);
Solution3DRISMR *out = dynamic_cast<Solution3DRISMR *>(out0);


Integer Nx,Ny,Nz;
Grid3DRISM *smallGrid = (Grid3DRISM *)in->getGrid();



Nx = smallGrid->getNx();
Ny = smallGrid->getNy();
Nz = smallGrid->getNz();

Grid3DRISM *largeGrid = (Grid3DRISM *)out->getGrid();

Integer largeXstride = largeGrid->getNy() * largeGrid->getNz();
Integer largeYstride = largeGrid->getNz();

Integer halfNx = Nx/2;
Integer halfNy = Ny/2;
Integer halfNz = Nz/2;

Integer numSites = in->getNumberOfSites();
Integer site;

out->setZero();

for(site=0;site<numSites;site++)
{
	Real *src = in->getGamma()[site];
	Real *dst = out->getGamma()[site];

	Integer x,y,z,x1,y1,z1;

	for(x=0;x<Nx;x++)
	for(y=0;y<Ny;y++)
	for(z=0;z<Nz;z++)
	{
		x1 = (x<=halfNx) ? x : x + Nx;
		y1 = (y<=halfNy) ? y : y + Ny;
		z1 = (z<=halfNz) ? z : z + Nz;

		dst[x1*largeXstride + y1*largeYstride + z1 ] = *src;
		src++;

	}//x,y,z

}//site


}
