#include "calculatePhiCoulomb2.h"

#include "Grid1DRISM.h"
#include "SphericalFFT.h"
#include "NgSiteSitePotential.h"
#include "TabFunction.h"

#include <stdlib.h>
#include <string.h>

// ----------  Calculating Phi a Coulomb Part (Phi):
// 		d3ifft(beta * 1/k^2 exp(-k^2/4t^2) * chi[i][j] )

void calculatePhiCoulomb2(	Grid1DRISM *grid,
				Real	KBT,
				TabFunction ***analyticChiIndex,
				Real **analyticChiMultipliers,
	
				Real ngCoeff,
				Integer numSolventSites,
				TabFunction **phi,	//out
				TabFunction ***phiIndex //out
			)
{
	int i,j;

	Integer N = grid->getN();
	Real dk = grid->getDK();

	Real *temp = (Real *)malloc( N * sizeof(Real) );
	SphericalFFT *sphericalFFT = SphericalFFT::getInstance();


	Real beta = 1/KBT;

	TabFunction **phiPtr = phi;

	for(i=0; i<numSolventSites; i++)
	{
		for(j=i; j<numSolventSites; j++,phiPtr++)
		{
			memcpy(temp,analyticChiIndex[i][j]->getTab(),N * sizeof(Real) );

			Integer m;
			Real k;
			Real *ptr = temp;

			Real factor = -beta; //* analyticChiMultipliers[i][j]; BECAUSE it will be multiplied by chiMul in calculateAnalyticalTheta2
			for( m=0,k=dk ; m<N; m++,k+=dk, ptr++ )
			{
				*ptr *= factor *
					NgSiteSitePotential::calculateNgPotential( 	
					1,		//Real q1, 
					1,		//Real q2, 
					ngCoeff,	//m_erfCoeffReal erfCoefficient, 
					k		//Real k
					);
			}
			
			sphericalFFT->d3ifft(	temp,			//Real *in,
						(*phiPtr)->getTab(),	//Real *out,
						grid			//Grid1DRISM *grid
					);			

			phiIndex[i][j] = *phiPtr;
			phiIndex[j][i] = *phiPtr;
		}
	}

	free(temp);

}
