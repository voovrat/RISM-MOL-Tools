#include "buildChi4.h"

#include "Settings.h"

#include "Grid3DRISM.h"
#include "TabFunction.h"
#include "Solution3DRISMK.h"
#include "Solution3DRISMR.h"
#include "buildSpherical.h"
#include "OmegaData.h"
#include "FFTW3D.h"
#include "buildKSphere.h"
#include "ArrayOperations.h"

//#include "UnaryFunctionOperations.h"
#include "buildSphericalK.h"
#include "buildSphericalK3.h"
#include "OmegaK.h"
#include "Grid1DRISM.h"
#include "SphericalFFT.h"

#include <stdlib.h>

#include "sinc.h"

#if DEBUG_NaN
#include "writeDoubleArrayToFile.h"
#include <stdio.h>
#endif


// because for multi-component systems if density[i] != density[j]
// chi[i][j] = density[i]*h[i][j] and 
// chi[j][i] = density[j]*h[j][i]
// because we do not want to store 2 times more functions, it is better to have
// a pre-multipliers for the chi functions
void buildChi4(TabFunction **rdfs,// array size= numSolventSites*(numSolventSites-1)/2
				  // elements g11, g12.. g1N, g22,...g2N... gNN
		Integer numSolventSites,
		OmegaData *omega,
		Real *densities,	//in Bohr^-3
		Solution3DRISMK **chi3D,	//out, coresponds to chi
		Solution3DRISMK ***chiIndex,	//out, numSolventSites*numSolventSites array
						// chiIndex[i][j] contains chi[i][j]
		Real **chiMultipliers // out
		)

{
	Integer i,j;

	Grid3DRISM *grid = (Grid3DRISM *)chi3D[0]->getGrid();

	Real dr = rdfs[0]->getTabStep();
	Integer N = rdfs[0]->getTabSize();

	Grid1DRISM grid1D(N,dr);

	Real dk = grid1D.getDK();

	Real *bufferK = (Real *)malloc( N * sizeof(Real));
	Real *bufferR = (Real *)malloc( N * sizeof(Real));

	SphericalFFT *sphFFT = SphericalFFT::getInstance();

	// Transform RDfs to the K-space and interpolate them to 3D grid
	TabFunction **rdfTab = rdfs;
	Solution3DRISMK **chiOut = chi3D;
	for(i=0;i<numSolventSites;i++)
		for(j=i;j<numSolventSites;j++, rdfTab++, chiOut++)
		{
			memcpy(	bufferR,		//void *dest, 
				(*rdfTab)->getTab(),	//const void *src, 
				N*sizeof(Real) 		//size_t n
				);

			addArrayScalar<Real,Real>(
					bufferR,	//DataType *dst,
					-1,		//ScalarType scalar,
					N		//Integer N
					);

			sphFFT->d3fft(	bufferR,	//Real *in,
					bufferK,	//Real *out,
					&grid1D		//Grid1DRISM *grid
			);
			
			TabFunction hk;
			
			hk.init(bufferK,	//Real *tab,
				N,		//Integer N,
				dk,		//Real x0,
				dk		//Real dx
				);
			printf("convert chi[%ld][%ld] to 3D ...\n ",i,j);
			
			(*chiOut)->setZero();

//			buildSphericalK3<Real>(	
			buildSphericalK<Real>(   //- diverges ??
						&hk,	//UnaryFunction<Real,ResultType> *fn,
						grid,		//Grid3DRISM *grid,
						(*chiOut)->getGamma()[0]	//std::complex<Real> *data3D,// out
						//Real drDivider=7 
						);



			Real coeff = 1;
	
			if(densities[i]==densities[j]) coeff*=densities[i];

			mulArrayScalar<std::complex<Real>,Real>(
						(*chiOut)->getGamma()[0],//DataType *dst,
						coeff,		//ScalarType scalar,
						(*chiOut)->getSizeOfOneGamma()	//Integer N
					);
			Real kx,ky,kz;
			Real dx = grid->getDRx();
			Real dy = grid->getDRy();
			Real dz = grid->getDRz();

#if MULTIPLY_CHI_BY_SINC
			KGAMMA_FOR_SOLUTION((*chiOut),0)
			{
				kx = KGAMMA_FOR_KX;
				ky = KGAMMA_FOR_KY;
				kz = KGAMMA_FOR_KZ;

				KGAMMA_FOR_DATA *= sinc(0.5*kx*dx) * sinc(0.5*ky*dy)*sinc(0.5*kz*dz);
			
				
			}
			END_KGAMMA_FOR_SOLUTION
#endif
			printf("done\n");

			if(densities[i] == densities[j])
			{
				chiMultipliers[i][j] = 1;
				chiMultipliers[j][i] = 1;
			}
			else
			{
				chiMultipliers[i][j] = densities[i];
				chiMultipliers[j][i] = densities[j];
			}

			chiIndex[i][j] = *chiOut;
			chiIndex[j][i] = *chiOut;
		}

	// add Omega Functions
	SolutionFactory3DRISMK solutionFactoryK(1);
	Solution3DRISMK *solutionK = (Solution3DRISMK*)solutionFactoryK.createSolution(grid);

	for(i=0;i<omega->getNumOmega();i++)
	{
		Integer chiID = omega->getOmegaID(i);
		Real omegaCoeff = omega->getOmegaCoeff()[i];
		Real omegaPosition = omega->getOmegaPosition()[i];

		OmegaK omegaK(omegaPosition,omegaCoeff);

		printf(" add %lf * omega(%lf) to RDF#%ld ...\n ",omegaCoeff,omegaPosition,chiID);

//		buildSphericalK3<Real>(	
		buildSphericalK<Real>(	 //- diverges???
					&omegaK,	//UnaryFunction<Real,ResultType> *fn,
					grid,		//Grid3DRISM *grid,
					chi3D[chiID]->getGamma()[0]	//std::complex<Real> *data3D,// out
					//Real drDivider=7 
					);

		printf("done\n");
		
	}

#ifdef STUPID_CHI_AVERAGING
// stupid chi averaging means that all chiK[i](k=0) are equal and are the mean of chi[j](k=0)
// However, this stupid averagin is stupid, because it will not work properly if one have several species with different density:
// then chi(k=0) should differ by the factor of density (see chiMultipliers), but we do average them, which is wrong...


	Integer chiID;

	chiID=0;
	std::complex<Real> SumChi = 0;
	Integer NumChi = 0;
	for(i=0;i<numSolventSites;i++)
		for(j=i;j<numSolventSites;j++, chiID++)
		{
			SumChi += chi3D[chiID]->getGamma()[0][0];
			NumChi ++;
			//char s[256];
			//sprintf(s,"chi%ld%ld.3d",i,j);
			//writeDoubleArrayToFile(s,(double *)chi3D[chiID]->getGamma()[0],chi3D[chiID]->getSizeOfOneGamma()*2);			

		}

	chiID=0;
	for(i=0;i<numSolventSites;i++)
		for(j=i;j<numSolventSites;j++, chiID++)
		{
			chi3D[chiID]->getGamma()[0][0] = SumChi/(Real)NumChi;
//			NumChi ++;
			//char s[256];
			//sprintf(s,"chi%ld%ld.3d",i,j);
			//writeDoubleArrayToFile(s,(double *)chi3D[chiID]->getGamma()[0],chi3D[chiID]->getSizeOfOneGamma()*2);			

		}


#endif


#if DEBUG_NaN
#define DEBUG_CHI 1
#endif

#if DEBUG_CHI
	chiID=0;
	for(i=0;i<numSolventSites;i++)
		for(j=i;j<numSolventSites;j++, chiID++)
		{
			char s[256];
			sprintf(s,"chi%ld%ld.3d",i,j);
			writeDoubleArrayToFile(s,(double *)chi3D[chiID]->getGamma()[0],chi3D[chiID]->getSizeOfOneGamma()*2);			

		}
#endif

	//NULL_DELETE(solutionR);
	free(bufferK);
	free(bufferR);
		
	//NULL_DELETE(solutionK);
}

