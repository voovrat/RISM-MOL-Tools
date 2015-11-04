#include "Operator3DRISM2.h"

#include <stdio.h>
#include <stdlib.h>

#include "GridIndependentInterface3DRISM.h"
#include "GridDependentInterface3DRISM.h"

#include "Closure3DRISM.h"
#include "Solution3DRISMR.h"
#include "Solution3DRISMK.h"
#include "SiteMultiplicities.h"

#include "mulSolutionByChiMatrix2.h"

#include "FFTW3D.h"
#include "FFTZero3D.h"

#include "Exception.h"

#include "TextLog.h"

#include "Settings.h"

Operator3DRISM2::Operator3DRISM2(	GridIndependentInterface3DRISM *gridIndependent,
				GridDependentInterface3DRISM *gridDependent
		)
		: Operator(gridIndependent,gridDependent)
{
	m_solutionFactoryR = NULL;
	m_solutionFactoryK = NULL;

	m_gridDependent3D = (GridDependentInterface3DRISM *)m_gridDependent;
	m_gridIndependent3D = (GridIndependentInterface3DRISM *)m_gridIndependent;

	
	m_cR=NULL;
	m_cK=NULL;
	m_gammaK=NULL;
}

Operator3DRISM2::~Operator3DRISM2()
{
	NULL_DELETE(m_cR)
	NULL_DELETE(m_cK)
	NULL_DELETE(m_gammaK)

	NULL_DELETE(m_solutionFactoryR);
	NULL_DELETE(m_solutionFactoryK);
}


void Operator3DRISM2::F(	Solution *gamma,
			Solution *result
		)
{
static Integer count=0;

	char s[256];
	sprintf(s,"F:%d\n",(int)count++);
	TextLog::getInstance()->printString(3,s);



	Solution3DRISMR *gamma3D = dynamic_cast<Solution3DRISMR *>(gamma);
	Solution3DRISMR *result3D = dynamic_cast<Solution3DRISMR *>(result);

	if(!gamma3D || !result3D)
		throw new Exception(this,"Operator3DRISM2::F : invalid class of arguments (should be Solution3DRISM )");

	m_numSolventSites = m_gridIndependent3D->getSiteMultiplicities()->getNumSites();

	m_grid = (Grid3DRISM *)gamma->getGrid();
	
	if(!m_solutionFactoryR)
		m_solutionFactoryR = new SolutionFactory3DRISMR(m_numSolventSites);

	if(!m_solutionFactoryK)
		m_solutionFactoryK = new SolutionFactory3DRISMK(m_numSolventSites);
	

	closure_step(gamma3D);		// m_cR = closure(gamma3D)

#if DEBUG_NaN

	if(count < 20)
	{
		char s[256];
		sprintf(s,"gamma0_%ld.3d",count);
		writeDoubleArrayToFile(s,gamma3D->getGamma()[0],gamma3D->getSizeOfOneGamma());

		sprintf(s,"gamma1_%ld.3d",count);
		writeDoubleArrayToFile(s,gamma3D->getGamma()[1],gamma3D->getSizeOfOneGamma());

		sprintf(s,"c0_%ld.3d",count);
		writeDoubleArrayToFile(s,m_cR->getGamma()[0],gamma3D->getSizeOfOneGamma());

		sprintf(s,"c1_%ld.3d",count);
		writeDoubleArrayToFile(s,m_cR->getGamma()[1],gamma3D->getSizeOfOneGamma());



	}

#endif

	


#if DEBUG_STRANGE_04

#define NNN 100
	static Real *gamma_dat=NULL;
	static Real *c_dat = NULL;

	Grid3DRISM *g3d = (Grid3DRISM *)gamma->getGrid();
	Integer N = g3d->getNz();
	Integer N2 = N*sizeof(Real);

	if(!gamma_dat) 
	{
		gamma_dat = (Real *)malloc(2*NNN*N2);
		c_dat = (Real *)malloc(2*NNN*N2);
		
	}	

	if(count<NNN)
	{
		memcpy(gamma_dat+2*(count-1)*N, gamma3D->getGamma()[0],N2);
		memcpy(gamma_dat+2*(count-1)*N+N, gamma3D->getGamma()[1],N2);
		memcpy(c_dat+2*(count-1)*N, m_cR->getGamma()[0],N2);
		memcpy(c_dat+2*(count-1)*N+N, m_cR->getGamma()[1],N2);
	}

	if(count==NNN)
	{
		writeDoubleArrayToFile("gamma_dat.txt",gamma_dat,2*NNN*N);
		writeDoubleArrayToFile("c_dat.txt",c_dat,2*NNN*N);
	}


#endif

	fft_step();			// m_cK = fft(m_cR)
	gamma_step();			// m_gammaK[i] = sum_j m_cK[j]*chi[j][i] - m_cK[i] 
	ifft_step(result3D);		//result = ifft(m_gammaK)
	addTheta_step(result3D); 	//result = result + theta


#if DEBUG_STRANGE_04

	if(count>NNN)
	{
		result3D->setZero();
	}
#endif

	// //////// Step 1: closure

	
}

void Operator3DRISM2::closure_step(Solution3DRISMR *gamma)
{
	if(!m_cR)
		m_cR = (Solution3DRISMR *)m_solutionFactoryR->createSolution(gamma->getGrid());

	Closure3DRISM *closure = m_gridDependent3D->getClosure();

	closure->calculateClosure(	gamma,		//Solution3DRISMR *gamma,	
				 	m_cR		//Solution3DRISMR *c_short//out
				);
}

void Operator3DRISM2::fft_step()
{
	if(!m_cK)
		m_cK = (Solution3DRISMK *)m_solutionFactoryK->createSolution(m_grid);

//	FFTW3D *fftw = FFTW3D::getInstance();

#if USE_FFT_ZERO
	FFTZero3D *fftw = FFTZero3D::getInstance();
#endif

#if USE_FFT_DELTA
	FFTW3D *fftw = FFTW3D::getInstance();
#endif

	Integer i;Real k;
	for(i=0;i<m_numSolventSites;i++)
	{

#if USE_FFT_DELTA
		k=
#endif
		fftw->fft(	m_cR->getGamma()[i],	//Real *in,
				m_cK->getGamma()[i],	//m_std::complex<Real> *out,
				m_grid			//Grid3DRISM *grid
			);
	}

#if USE_FFT_DELTA
	mulScalarSolution3DRISMK(m_cK,k);
#endif

	NULL_DELETE(m_cR);
}

void Operator3DRISM2::gamma_step()
{
	if(!m_gammaK)
		m_gammaK = (Solution3DRISMK *)m_solutionFactoryK->createSolution(m_grid);



	mulSolutionByChiMatrix2(m_cK,		//Solution3DRISMK *solution,
				m_gridIndependent3D->getSiteMultiplicities(),	//SiteMultiplicities *,
				m_gridDependent3D->getChiIndex(), 		//Solution3DRISMK ***chiIndex,
				m_gridDependent3D->getChiMultipliers(),
				m_gammaK		//  Solution3DRISMK *result
			); // m_gammaK[i] = sum_j m_cK[j] * chi[j][i]
	
	subSolution3DRISMK(m_gammaK,m_cK);
			// m_gammaK[i] = sum_j m_cK[j] * chi[j][i] - m_cK[i]

//	addSolution3DRISMK(m_gammaK,m_gridDependent3D->getTheta());
			// m_gammaK[i] = sum_j m_cK[j] * chi[j][i] - m_cK[i] + theta[i]

	NULL_DELETE(m_cK);
}


void Operator3DRISM2::ifft_step(Solution3DRISMR *result)
{

#if USE_FFT_DELTA
	FFTW3D *fftw = FFTW3D::getInstance();
#endif
#if USE_FFT_ZERO
	FFTZero3D *fftw = FFTZero3D::getInstance();
#endif

	Integer i;Real k;
	for(i=0;i<m_numSolventSites;i++)
	{
#if USE_FFT_DELTA
		k= 
#endif
		fftw->ifft(	m_gammaK->getGamma()[i],//std::complex<Real> *in,
				result->getGamma()[i],	//Real *out,
				m_grid			//Grid3DRISM *grid
		);
	}

#if USE_FFT_DELTA
	mulScalarSolution3DRISMR(result,k);
#endif

	NULL_DELETE(m_gammaK);
}

void Operator3DRISM2::addTheta_step(Solution3DRISMR *result)
{

	addSolution3DRISMR(result, m_gridDependent3D->getThetaR());

}





Operator *OperatorFactory3DRISM2::createOperator(
					GridIndependentData *gridIndependent,
					GridDependentData *gridDependent)
{
	GridIndependentInterface3DRISM *gridIndependent3 =
		dynamic_cast<GridIndependentInterface3DRISM *>(gridIndependent);

	GridDependentInterface3DRISM *gridDependent3 = 
		dynamic_cast<GridDependentInterface3DRISM *>(gridDependent);

	if(!gridIndependent3 || !gridDependent3)
		throw new Exception(this,"OperatorFactory3DRISM::createOperator : invalid class of arguments (should be GridIndependet3DRISM and GridDependent3DRISM)");

	return new Operator3DRISM2(gridIndependent3,gridDependent3);
}
