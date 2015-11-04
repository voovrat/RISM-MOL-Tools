#include "calculatePhiLJ2.h"

#include "Grid1DRISM.h"
#include "SphericalFFT.h"
#include "TabFunction.h"

#include <stdlib.h>
#include <string.h>

#include "ArrayOperations.h"



// PhiLJ[i][j] = beta * d3ifft( d3fft(U_LJ_long) * chi[i][j] )
// U_LJ_long = -1/r^6 if r<R_cut -1/R_cut^6 else

void calculatePhiLJ2(	Grid1DRISM *grid,
			Real KBT,
			TabFunction ***analyticChiIndex,
			Real **analyticChiMultipliers,
			Real ljPotentialCutoff,	
			Integer numSolventSites,
			TabFunction **phi,	//out
			TabFunction ***phiIndex //out
			)
{

Real dR = grid->getDR();
Integer N = grid->getN();

Real beta = 1/KBT;

// Calculating the Lennard Jones Part (PhiLJ)
Real *U_LJ_long = (Real *)malloc( N * sizeof(Real) ); // U_LJ_long = -1/r^6  if r>R_cut
						      //             -1/R_cut^6 else
// generate the function U_LJ_long = -1/r^6 if r<R_cut -1/R_cut^6 else
Real r=dR;
Real *ptrLJ = U_LJ_long;

Real Rcut2 = ljPotentialCutoff*ljPotentialCutoff;
Real Rcut6 = Rcut2 * Rcut2 * Rcut2;
Real CutoffConstant = -beta/Rcut6;

SphericalFFT *sphericalFFT = SphericalFFT::getInstance();


Integer i,j;

for(i=0;i<N; i++,r+=dR,ptrLJ++)
{
	if(r<ljPotentialCutoff)
	{
		*ptrLJ = CutoffConstant;
	}
	else
	{
	Real r2 = r*r;
	Real r6 = r2*r2*r2;

	*ptrLJ = -beta/r6;
	}
}

// perform the Fourier transform of the U_LJ_long

Real *U_LJ_long_K = (Real *)malloc( N * sizeof(Real) ); // U_LJ_long_K = d3fft(U_LJ_long)
Real *temp = (Real *)malloc( N * sizeof(Real));


sphericalFFT->d3fft(	U_LJ_long,	//Real *in,
			U_LJ_long_K,	//Real *out,
			grid		//Grid1DRISM *grid
		);

free(U_LJ_long);
U_LJ_long=NULL;

// perform the convolutions
TabFunction **phiLJPtr = phi;

for(i=0; i<numSolventSites; i++)
{
	for(j=i; j<numSolventSites; j++,phiLJPtr++)
	{
		memcpy(temp,analyticChiIndex[i][j]->getTab(),N * sizeof(Real) ); // temp = chi[i][j]

		//temp = chi[i][j] * d3fft(U_LJ_long)
		mulArray<Real>(	temp,		//	DataType *dst,
				U_LJ_long_K,	//DataType *src,
				N		//Integer N
				);		
	
//		Real chiMultiplier = analyticChiMultipliers[i][j];
		Real chiMultiplier = 1; //BECAUSE it will be multiplied in calcualteAnalyticalTheta2
	
		mulArrayScalar<Real,Real>(	temp,	//DataType *dst,
						chiMultiplier, //ScalarType scalar,
						N //Integer N
						);

		//*phiLJPtr = d3ifft( chi[i][j] * d3fft(U_LJ_long) )
		sphericalFFT->d3ifft(	temp,			//Real *in,
					(*phiLJPtr)->getTab(),	//Real *out,
					grid			//Grid1DRISM *grid
				);			

		phiIndex[i][j] = *phiLJPtr;
		phiIndex[j][i] = *phiLJPtr;
	}
}

free(U_LJ_long_K); 
U_LJ_long_K=NULL;

free(temp);
temp = NULL;


}

