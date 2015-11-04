#include "buildChi1DRISM.h"

#include <stdlib.h>

#include "Grid1DRISM.h"
#include "TabFunction.h"
#include "OmegaData.h"
#include "SphericalFFT.h"
#include "ArrayOperations.h"

// because for multi-component systems if density[i] != density[j]
// chi[i][j] = density[i]*h[i][j] and 
// chi[j][i] = density[j]*h[j][i]
// because we do not want to store 2 times more functions, it is better to have
// a pre-multipliers for the chi functions
void buildChi1DRISM(TabFunction **rdfs,// array size= numSolventSites*(numSolventSites-1)/2
				  // elements g11, g12.. g1N, g22,...g2N... gNN
		Integer numSolventSites,
		OmegaData *omega,
		Real *densities,	//in Bohr^-3
		TabFunction **chi,	//out, coresponds to chi
		TabFunction ***chiIndex,	//out, numSolventSites*numSolventSites array
						// chiIndex[i][j] contains chi[i][j]
		Real **chiMultipliers // out
		)

{
	Integer i,j;

	Integer N = rdfs[0]->getTabSize();
	Integer DataSize = N * sizeof(Real);
	Real dR = rdfs[0]->getTabStep();

	Grid1DRISM grid(N,dR);

	Real *temp = (Real *)malloc( DataSize );

	SphericalFFT *sphericalFFT=SphericalFFT::getInstance();


	// Transform RDfs to the K-space
	TabFunction **rdfTab = rdfs;
	TabFunction **chiOut = chi;
	for(i=0;i<numSolventSites;i++)
		for(j=i;j<numSolventSites;j++, rdfTab++, chiOut++)
		{

			memcpy(temp, (*rdfTab)->getTab(), DataSize);
			subArrayScalar<Real,Real>(	temp,		//DataType *dst,
							1,		//ScalarType scalar,
							N		//Integer N
							);

			sphericalFFT->d3fft(	temp,		 	//Real *in,
						(*chiOut)->getTab(),	//Real *out,
						&grid	 	 	//Grid1DRISM *grid
						);		

			if(densities[i] == densities[j])
			{
				mulArrayScalar<Real,Real>((*chiOut)->getTab(),		//DataType *dst,
							  densities[i],		//ScalarType scalar,
							  N		//Integer N
							);
	
				chiMultipliers[i][j] = 1;
				chiMultipliers[j][i] = 1;
			}	
			else	// densities[i] != densities[j]
			{
				chiMultipliers[i][j] = densities[i];
				chiMultipliers[j][i] = densities[j];
			}
			
			chiIndex[i][j] = *chiOut;
			chiIndex[j][i] = *chiOut;
		}
	
	free(temp);
	temp = NULL;

	// add Omega Functions
	for(i=0;i<omega->getNumOmega();i++)
	{
		Integer chiID = omega->getOmegaID(i);
		Real omegaCoeff = omega->getOmegaCoeff()[i];
		Real omegaPosition = omega->getOmegaPosition()[i];


		Real *data = chi[chiID]->getTab();
		if(omegaPosition==0)
		{
			addArrayScalar<Real,Real>(	data,		//DataType *dst,
							omegaCoeff,	//ScalarType scalar,
							N		//Integer N
							);

		}
		else // omegaPosition != 0
		{
			Real *ptr = data;
			Integer j;
			Real k;
			Real dk = grid.getDK();
			for( j=0, k=dk; j<N; j++, k+=dk, ptr++ )
			{
				*ptr += omegaCoeff * sin( k * omegaPosition) / k / omegaPosition;
			}

		}// if omegaPosition

	}
}

