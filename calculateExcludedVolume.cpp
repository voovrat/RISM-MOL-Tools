#include "calculateExcludedVolume.h"

#include "Settings.h"

#include "Grid3DRISM.h"
#include "TabFunction.h"
#include "Solution3DRISMR.h"

#include "calculateCompressibility.h"


// THE FUNCTION IS ONLY VALID FOR ONE COMPONENT SYSTEMS !!!

// V =  kappa ( 1- sum int c_alpha dr ) [ Bohr^3 ]

// Warning! Function work for one component solutions
// Result - in rdf units (Bohr^3) 

// kappa = 1/denity + 4 pi int (g - 1)r^2 dr [ Bohr^3 ]

double	calculateExcludedVolume(	TabFunction **solventRDFs, 
					Solution3DRISMR *gamma,//unused	
					Solution3DRISMR *c,
					Real *densities,  
					Integer *multiplicities
			 	)
{


	Real kappa = calculateCompressibility(	solventRDFs[0],		//TabFunction *rdf,
						densities[0]		//Real density
						);

//	Real density = densities[0];

	Grid3DRISM	*grid = (Grid3DRISM *)c->getGrid();


	Integer Nsites = c->getNumberOfSites();
	Integer site;
	
	Real SumC = 0;
	for ( site =0; site<Nsites; site++)
	{
		Real *c_ptr = c->getGamma()[site];
		Integer N = c->getSizeOfOneGamma();

		while(N--)
		{
			SumC += *c_ptr * multiplicities[site];
			c_ptr++;
		}
	}

	Real IntC = SumC * grid->getDRx() * grid->getDRy() * grid->getDRz();

	Real V = kappa * (1-densities[0]*IntC);

	return V;
}
