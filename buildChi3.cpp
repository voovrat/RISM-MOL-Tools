#include "buildChi3.h"

#include "Grid3DRISM.h"
#include "TabFunction.h"
#include "Solution3DRISMK.h"
#include "Solution3DRISMR.h"

#include "buildSpherical.h"
#include "buildSpherical2.h"
#include "buildSpherical4.h"

#include "OmegaData.h"
#include "FFTW3D.h"
#include "drawDeltaSphere3.h"
#include "drawDeltaSphere4.h"
#include "drawDeltaSphere5.h"
#include "buildKSphere.h"
#include "ArrayOperations.h"


#include "writeDoubleArrayToFile.h"

// because for multi-component systems if density[i] != density[j]
// chi[i][j] = density[i]*h[i][j] and 
// chi[j][i] = density[j]*h[j][i]
// because we do not want to store 2 times more functions, it is better to have
// a pre-multipliers for the chi functions
void buildChi3(TabFunction **rdfs,// array size= numSolventSites*(numSolventSites-1)/2
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



	SolutionFactory3DRISMR solutionFactoryR(1);
	Solution3DRISMR *solutionR = (Solution3DRISMR*)solutionFactoryR.createSolution(grid);
	
	FFTW3D *fftw=FFTW3D::getInstance();

	
	Real fftk;

	// Transform RDfs to the K-space
	TabFunction **rdfTab = rdfs;
	Solution3DRISMK **chiOut = chi3D;
	for(i=0;i<numSolventSites;i++)
		for(j=i;j<numSolventSites;j++, rdfTab++, chiOut++)
		{
		printf("build spherical solvent RDF (%ld,%ld)\n",i,j);
#if USE_buildSpherical		
			buildSpherical(	
					*rdfTab,//UnaryFunction<Real,Real> *fn,
					grid,	//Grid3DRISM *grid,
					solutionR->getGamma()[0]//Real *data3D// out
					);

#endif
#if USE_buildSpherical2
			buildSpherical2(	
					*rdfTab,//UnaryFunction<Real,Real> *fn,
					grid,	//Grid3DRISM *grid,
					solutionR->getGamma()[0]//Real *data3D// out
			);
#endif
#if USE_buildSpherical4
			buildSpherical4(	
					*rdfTab,//UnaryFunction<Real,Real> *fn,
					grid,	//Grid3DRISM *grid,
					solutionR->getGamma()[0]//Real *data3D// out
			);
#endif



			subArrayScalar<Real,Real>
					(	solutionR->getGamma()[0],//DataType *dst,
						1,		//ScalarType scalar,
						solutionR->getSizeOfOneGamma()	//Integer N
					);
	

			fftk=fftw->fft(	solutionR->getGamma()[0],//Real *in,
					(*chiOut)->getGamma()[0],//std::complex<Real> *out,
					grid		//Grid3DRISM *grid
				);

			Real coeff = fftk;
	
			if(densities[i]==densities[j]) coeff*=densities[i];

			mulArrayScalar<std::complex<Real>,Real>(
						(*chiOut)->getGamma()[0],//DataType *dst,
						coeff,		//ScalarType scalar,
						(*chiOut)->getSizeOfOneGamma()	//Integer N
					);

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
			printf("...done\n");
		}

	// add Omega Functions
	SolutionFactory3DRISMK solutionFactoryK(1);
	Solution3DRISMK *solutionK = (Solution3DRISMK*)solutionFactoryK.createSolution(grid);

	for(i=0;i<omega->getNumOmega();i++)
	{
		Integer chiID = omega->getOmegaID(i);
		Real omegaCoeff = omega->getOmegaCoeff()[i];
		Real omegaPosition = omega->getOmegaPosition()[i];

		printf("add %lf *  omega R=%lf to RDF # %ld\n",omegaCoeff,omegaPosition,chiID);
#ifdef USE_REAL_OMEGA
		solutionR->setZero();

#if USE_drawDeltaSphere3
		drawDeltaSphere3(omegaPosition,			//Real R,
				solutionR->getGamma()[0],	//Real *data,
				grid				//Grid3DRISM *
				);
#endif
#if USE_drawDeltaSphere5
		drawDeltaSphere5(omegaPosition,	//Real R,
				 solutionR->getGamma()[0],	//Real *data,
				 grid				//Grid3DRISM *,
      			 //Real dtheta = 0.01,
      			//Real dphi = 0.01
				);
#endif
#if USE_drawDeltaSphere4

	drawDeltaSphere4(omegaPosition,	//Real R,
			 solutionR->getGamma()[0],	//Real *data,
			 grid				//Grid3DRISM *,
			 //Real dtheta = 0.01,
			//Real dphi = 0.01
			);
#endif
		


		fftk=fftw->fft(	solutionR->getGamma()[0],//Real *in,
				solutionK->getGamma()[0],//std::complex<Real> *out,
				grid		//Grid3DRISM *grid
      			// Integer RADIUS_FACTOR = 5
				);

      
      	
		Real coeff = fftk * omegaCoeff;


#else//USE_REAL_OMEGA
	solutionK->setZero();
#if USE_buildKSphere 
	buildKSphere(	omegaPosition,			//Real R,
		     	solutionK->getGamma()[0],	//std::complex<Real> *data,
			grid				//Grid3DRISM *grid
		   );


#endif
	Real coeff = omegaCoeff;
#endif // USE_REAL_OMEGA
		mulArrayScalar<std::complex<Real>,Real>(
						solutionK->getGamma()[0],//DataType *dst,
						coeff,		//ScalarType scalar,
						solutionK->getSizeOfOneGamma()	//Integer N
					);
		// chi += omega
		addArray<std::complex<Real> >(
				chi3D[chiID]->getGamma()[0],	//DataType *dst,
				solutionK->getGamma()[0],	//DataType *src,
				solutionK->getSizeOfOneGamma()	//Integer N
				);
		printf("...done\n");
	}


#if DEBUG_CHI
	Integer chiID=0;
	printf("saving chi to files...");
	for(i=0;i<numSolventSites;i++)
		for(j=i;j<numSolventSites;j++, chiID++)
		{
			char s[256];
			sprintf(s,"chi%ld%ldR.3d",i,j);
			writeDoubleArrayToFile(s,(double *)chi3D[chiID]->getGamma()[0],chi3D[chiID]->getSizeOfOneGamma()*2);			

		}
	printf("...done\n");
#endif



	NULL_DELETE(solutionR);
	NULL_DELETE(solutionK);
}

