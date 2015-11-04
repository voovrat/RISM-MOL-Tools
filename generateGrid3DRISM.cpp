#include "generateGrid3DRISM.h"

#include "MoleculeCoordinates.h"
#include "Grid3DRISM.h"

#define INF 1e9

void generateGrid3DRISM(MoleculeCoordinates *coors,
			Real buffer,
			Real dr,	
			Grid3DRISM *result, //out
			Integer  align
			)
{

	Integer Nsites = coors->getNumSites();

	Real minX = INF;
	Real maxX = -INF;

	Real minY = INF;
	Real maxY = -INF;

	Real minZ = INF;
	Real maxZ = -INF;
	Integer i;
	for(i=0;i<Nsites;i++)
	{
		if(coors->getX()[i]<minX) minX = coors->getX()[i];
		if(coors->getX()[i]>maxX) maxX = coors->getX()[i];

		if(coors->getY()[i]<minY) minY = coors->getY()[i];
		if(coors->getY()[i]>maxY) maxY = coors->getY()[i];

		if(coors->getZ()[i]<minZ) minZ = coors->getZ()[i];
		if(coors->getZ()[i]>maxZ) maxZ = coors->getZ()[i];
		
	}	

	Integer Nx = (Integer)((maxX-minX+2*buffer)/dr);
	Integer Ny = (Integer)((maxY-minY+2*buffer)/dr);
	Integer Nz = (Integer)((maxZ-minZ+2*buffer)/dr);

	Nx = (Nx+align-1)/align*align;
	Ny = (Ny+align-1)/align*align;
	Nz = (Nz+align-1)/align*align;

	Grid3DRISM grid(Nx,Ny,Nz,dr,dr,dr);

	grid.copy(result);
}	


