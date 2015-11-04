#include "calculateTheta2.h"

#include <stdlib.h>

#include "MoleculeCoordinates.h"
#include "SiteMultiplicities.h"
#include "SiteSitePotential.h"
#include "Solution3DRISMK.h"

#include "buildPotentialK.h"

//#include <complex>

//#include "ArrayOperations.h"

#include "mulSolutionByChiMatrix2.h"

void calculateTheta2(	Real beta,
			MoleculeCoordinates *soluteCoors,
			SiteMultiplicities *siteMultiplicities,
			SiteSitePotential *longPotentialK,
			Solution3DRISMK ***chiIndex,
			Real **chiMultipliers,
			Solution3DRISMK *theta,			// out
			Solution3DRISMK *betaUlong		//out[optional]
		   )
{
	Integer numSolventSites = siteMultiplicities->getNumSites();
	Integer i,j;	

	SolutionFactory3DRISMK solutionFactory(numSolventSites);
	Grid3DRISM *grid = (Grid3DRISM *)theta->getGrid();

	Integer delBetaUlong = 0;

	if(!betaUlong)
	{	betaUlong = (Solution3DRISMK *)solutionFactory.createSolution(grid);
		delBetaUlong = 1;
	}
	

	buildPotentialK (
			soluteCoors,	//MoleculeCoordinates *soluteCoors,
			longPotentialK,		//SiteSitePotential *siteSitePotential,
			betaUlong		//Solution3DRISMR *potential3D // output
	);	
		

	mulScalarSolution3DRISMK(betaUlong,-beta);

	// theta[i] = sum_j  betaU[j] * chi[j][i]
	mulSolutionByChiMatrix2(	betaUlong,		//Solution3DRISMK *solution,
				siteMultiplicities,	//SiteMultiplicities *,
				chiIndex,		//Solution3DRISMK ***chiIndex,
				chiMultipliers,		//Real **chiMultipliers
				theta			//Solution3DRISMK *result
			);

	if(delBetaUlong) NULL_DELETE(betaUlong);
}
