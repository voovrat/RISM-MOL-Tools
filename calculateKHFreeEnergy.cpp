#include "calculateKHFreeEnergy.h"

#include "Settings.h"

#include "Grid3DRISM.h"
#include "Solution3DRISMR.h"

double	calculateKHFreeEnergy(	Solution3DRISMR *gamma,	
				Solution3DRISMR *c,
				Solution3DRISMR *minusBetaUlong,
				Real kBT,
				Real *densities,
				Integer *multiplicities
			 	)
{
	Grid3DRISM	*grid = (Grid3DRISM *)gamma->getGrid();

	SolutionFactory3DRISMR solutionFactory(gamma->getNumberOfSites());

	Solution3DRISMR *h = (Solution3DRISMR *)solutionFactory.createSolution(grid);
	Solution3DRISMR *c_long = (Solution3DRISMR *)solutionFactory.createSolution(grid);


	gamma->copy(h);
	addSolution3DRISMR(h,c);	

	c->copy(c_long);
	addSolution3DRISMR(c_long,minusBetaUlong);

	Integer N;

	Real freeEnergy=0;

	Real *h_ptr;
	Real *c_ptr;
	Real S;
	Real ThH2;

	Integer site;
	for(site = 0; site<h->getNumberOfSites(); site++)
	{
		h_ptr = h->getGamma()[site];
		c_ptr = c_long->getGamma()[site];

		S = 0;
		N = h->getSizeOfOneGamma();
		

		while(N--)
		{
			ThH2 = (*h_ptr>0) ? 0 : *h_ptr * *h_ptr;		

			S+=ThH2/2 - *c_ptr - 0.5*(*h_ptr * *c_ptr);
			h_ptr++;
			c_ptr++;
		}

#if DEBUG_FREE_ENERGY
	printf("site %ld: sum=%lf\n",site,S);
#endif

	freeEnergy += kBT*densities[site]* S * multiplicities[site] *
				grid->getDRx() * grid->getDRy() * grid->getDRz();

	}

	NULL_DELETE(h);
	NULL_DELETE(c_long);

	return freeEnergy;
}
