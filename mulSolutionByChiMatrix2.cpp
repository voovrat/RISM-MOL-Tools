#include "mulSolutionByChiMatrix2.h"

#include <stdlib.h>
#include <string.h>

#include <complex>

#include "Solution3DRISMK.h"
#include "SiteMultiplicities.h"

#include "ArrayOperations.h"


void mulSolutionByChiMatrix2(	Solution3DRISMK *solution,
				SiteMultiplicities *siteMultiplicities,
				Solution3DRISMK ***chiIndex,
				Real **chiMultiplier,
				Solution3DRISMK *result
			)
{	Integer i,j;
		
	Integer *multiplicity = siteMultiplicities->getSiteMultiplicities();
	Integer numSolventSites = siteMultiplicities->getNumSites();

	result->setZero();
	
	Integer N = result->getSizeOfOneGamma();

	std::complex<Real> *tmp = (std::complex<Real> *)
				 malloc( N * sizeof(std::complex<Real> ) );

	// result[i] = sum_j Multiplicity[j] * solution[j] * chi[j][i]

	for(i=0;i<numSolventSites;i++)
	{
		for(j=0;j<numSolventSites;j++)
		{
		copyArray<std::complex<Real> >(tmp,				// dst
						solution->getGamma()[j],	//src
						N				//N
						); // tmp = solution[j]

		mulArray<std::complex<Real> >(tmp,				// dst
						chiIndex[j][i]->getGamma()[0],	//src
						N				//N
						); // tmp = solution[j] * chi[j][i]

		if(chiMultiplier[j][i]!=1)
		{
			mulArrayScalar<std::complex<Real> >(tmp,				// dst
						chiMultiplier[j][i],	//src  // NB: chiMultiplier[j][i], because we are multiplying by the density of the running solvent atom!
						N				//N
						); // tmp = solution[j] * chi[j][i]

		}

		if(multiplicity[j]!=1)
		{ 
			mulArrayScalar<std::complex<Real>,Integer> 
						(tmp,				//dst
						 multiplicity[j],		//Scalar
						 N				//N
						); // tmp = m[j] * solution[j] * chi[j][i]
		}

		addArray<std::complex<Real> >(result->getGamma()[i],		//dst
						tmp,				//src
						N				//N
						); // result[i] += m[j] * solution[j] * chi[j][i]
		}//j
	}//i

	free(tmp);
}
