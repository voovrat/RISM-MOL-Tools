#include "buildPotential3.h"

#include "MoleculeCoordinates.h"
#include "SiteSitePotential.h"
#include "Solution3DRISMR.h"

#include <math.h>

void buildPotential3 (
	MoleculeCoordinates *soluteCoors,
	SiteSitePotential *siteSitePotential,
	Real beta,
	Solution3DRISMR *potential, // output
	Real divider
)
{

if(!potential->getData())
	potential->createGamma();

Integer soluteSite, solventSite;
Integer NSolventSites = siteSitePotential->getNumSolventSites();
Integer NSoluteSites = siteSitePotential->getNumSoluteSites();

Grid3DRISM *grid = (Grid3DRISM *)potential->getGrid();

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

Real dV = 1.0 / (divider * divider * divider);

Integer offset;
Real x,y,z;

potential->setZero();

for(solventSite = 0; solventSite < NSolventSites; solventSite++)
{
	//GAMMA_FOR_SOLUTION(potential,solventSite)
	//{

	Real *data = potential->getGamma()[solventSite];
	
	for( x= Xmin; x<Xmax; x+=step_x )
	for( y= Ymin; y<Ymax; y+=step_y )
	for( z= Zmin; z<Zmax; z+=step_z )
	{
		offset = getXYZOffset(	x,		//Real x,
					y,		//Real y,
					z,		//Real z,
					grid		//Grid3DRISM *grid
					);
	 	
		if(offset<0) continue;

		Real U=0;

		for(soluteSite=	0; soluteSite <NSoluteSites; soluteSite++)
		{
			Real dx = x - soluteCoors->getX()[soluteSite];
			Real dy = y - soluteCoors->getY()[soluteSite];
			Real dz = z - soluteCoors->getZ()[soluteSite];
		
			Real R = sqrt(dx*dx + dy*dy + dz*dz);

			U+= siteSitePotential->calculatePotential(
					soluteSite, 
					solventSite,
					R) 
					;

		} // soluteSite

		data[offset]+=exp(-beta*U)*dV;
	}//xyz

}//for solventSite

Integer N = potential->getTotalSizeOfGamma();
Real *ptr = potential->getRawData();
while(N--)
{
*ptr = -1/beta*log(*ptr);
ptr++;
}

}
