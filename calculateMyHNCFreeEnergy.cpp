#include "calculateMyHNCFreeEnergy.h"

#include "Settings.h"

#include "Grid3DRISM.h"
#include "Solution3DRISMR.h"

// in 6D OZ + HNC we have:
//  DeltaG = int ( h^2/2 - hc/2 -c).
// in 3DRISM we have : c = sum c_alpha.
//
//  Thus, to be rigorous:
//  DeltaG = int h^2/2 - sum int h c_alpha/2 - sum int c_alpha 
//
//  averaging over angles we have:
//
//    DeltaG = int mean(h^2/2) - sum int h_alpha c_alpha/2 - sum int c_alpha...
//
//  In a rude approximation we can take: h = 1/Nsite h_alpha, and calculate the formula above...
//

double	calculateMyHNCFreeEnergy(
				Solution3DRISMR *gamma,	
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

	Integer Nsites =h->getNumberOfSites(); 
	for(site = 0; site<Nsites; site++)
//	for(site=0;site<;site++)

	{
		h_ptr = h->getGamma()[0];
		c_ptr = c_long->getGamma()[site];

		S = 0;
		N = h->getSizeOfOneGamma();
		

		while(N--)
		{
			//ThH2 = (*h_ptr>0) ? 0 : *h_ptr * *h_ptr;		

			//S+=ThH2/2 - *c_ptr - 0.5*(*h_ptr * *c_ptr);
			S+= (*h_ptr * *h_ptr) / 2/Nsites -*c_ptr - 0.5*(*h_ptr * *c_ptr);
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
