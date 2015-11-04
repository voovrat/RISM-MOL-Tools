#include "buildPotential.h"

#include "MoleculeCoordinates.h"
#include "SiteSitePotential.h"
#include "Solution3DRISMR.h"

void buildPotential (
	MoleculeCoordinates *soluteCoors,
	SiteSitePotential *siteSitePotential,
	Solution3DRISMR *potential // output
)
{

if(!potential->getData())
	potential->createGamma();

Integer soluteSite, solventSite;
Integer NSolventSites = siteSitePotential->getNumSolventSites();
Integer NSoluteSites = siteSitePotential->getNumSoluteSites();

for(solventSite = 0; solventSite < NSolventSites; solventSite++)
{
	GAMMA_FOR_SOLUTION(potential,solventSite)
	{
	 	GAMMA_FOR_DATA = 0;
		for(soluteSite=	0; soluteSite <NSoluteSites; soluteSite++)
		{
			Real dx = GAMMA_FOR_X - soluteCoors->getX()[soluteSite];
			Real dy = GAMMA_FOR_Y - soluteCoors->getY()[soluteSite];
			Real dz = GAMMA_FOR_Z - soluteCoors->getZ()[soluteSite];
		
			Real R = sqrt(dx*dx + dy*dy + dz*dz);

			GAMMA_FOR_DATA += siteSitePotential->calculatePotential(
					soluteSite, 
					solventSite,
					R);

		} // soluteSite
	}
	END_GAMMA_FOR_SOLUTION   

}//for solventSite


}
