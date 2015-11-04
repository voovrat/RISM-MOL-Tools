#include "HNCFreeEnergy3DRISM.h"

#include "Solution3DRISMR.h"
#include "FFTW3D.h"

#include "Solution3DRISMR.h"
#include "Solution3DRISMK.h"
#include "Grid3DRISM.h"
#include "Closure3DRISM.h"
#include "ArrayOperations.h"
#include "Exception.h"
#include "GridIndependentInterface3DRISM.h"
#include "GridDependentInterface3DRISM.h"
#include "Exception.h"
#include "SiteDensities.h"


HNCFreeEnergy3DRISM::HNCFreeEnergy3DRISM(
			Closure3DRISM *closure,
		//	Solution3DRISMK *betaUlongPotK,//-betaUlong
			SolutionFactory3DRISMR *solutionFactory,
			Real *densities, //[Bohr^-3]
			Integer *multiplicities,
			Real kBT	//[Hartree]
		)
{
	m_densities = densities;
	m_multiplicities = multiplicities;
	m_kBT = kBT;

	FFTW3D *fftw = FFTW3D::getInstance();

	m_closure = closure;
	m_solutionFactory = solutionFactory;
/*	if(betaUlongPotK)
	{
		m_grid = (Grid3DRISM *)betaUlongPotK->getGrid();
		m_longPot = (Solution3DRISMR *)m_solutionFactory->createSolution(m_grid);

		Real k;
		Integer site;
		Integer numSites = betaUlongPotK->getNumberOfSites();
		for(site=0;site<numSites;site++)
		{

			k = fftw->ifft(	
				betaUlongPotK->getGamma()[site], //std::complex<Real> *in,
				m_longPot->getGamma()[site],  //Real *out,
				m_grid			//Grid3DRISM *grid
			);
	
			mulArrayScalar<Real,Real>(
				m_longPot->getGamma()[site],	//DataType *dst,
				k,				//ScalarType scalar,
				m_longPot->getSizeOfOneGamma()	//Integer N
			);
		}//for site
	}//if
	else m_longPot=NULL;*/
	
}

HNCFreeEnergy3DRISM::~HNCFreeEnergy3DRISM()
{
//	if(m_longPot) NULL_DELETE(m_longPot);
//	m_longPot = NULL;
}

Real HNCFreeEnergy3DRISM::calculateFreeEnergy(Solution *gamma0)
{
	Solution3DRISMR *gamma = dynamic_cast<Solution3DRISMR *>(gamma0);
	if(!gamma)
		throw new Exception(this,"HNCFreeEnergy3DRISM::calculateFreeEnergy : invalid class of gamma");

	m_grid = (Grid3DRISM *)gamma0->getGrid();

	Solution3DRISMR *c = (Solution3DRISMR *)m_solutionFactory->createSolution(m_grid);
	Solution3DRISMR *h = (Solution3DRISMR *)m_solutionFactory->createSolution(m_grid);

	m_closure->calculateClosure(gamma,c);

	gamma->copy(h);
	addSolution3DRISMR(h,c);	

//	if(m_longPot)
//		addSolution3DRISMR(c,m_longPot);

	Integer N;

	Real freeEnergy=0;

	Integer site;
	for(site = 0; site<h->getNumberOfSites(); site++)
	{
		Real *h_ptr = h->getGamma()[site];
		Real *c_ptr = c->getGamma()[site];

		Real S = 0;

		N = h->getSizeOfOneGamma();

		while(N--)
		{
			S+=(*h_ptr * *h_ptr)/2 - *c_ptr - 0.5*(*h_ptr * *c_ptr);
			h_ptr++;
			c_ptr++;
		}

	freeEnergy += m_kBT*m_densities[site]* S * m_multiplicities[site] *
				m_grid->getDRx() * m_grid->getDRy() * m_grid->getDRz();

	}

	NULL_DELETE(h);
	NULL_DELETE(c);

	return freeEnergy;
}

FreeEnergy *HNCFreeEnergyFactory3DRISM::createFreeEnergy(GridDependentData *gridDependent)
{
	GridDependentInterface3DRISM *gridDependent3D = 
		dynamic_cast<GridDependentInterface3DRISM*>(gridDependent);


	GridIndependentInterface3DRISM *gridIndependent3D =
		dynamic_cast<GridIndependentInterface3DRISM*>(gridDependent->getGridIndependent());


	if(!gridDependent3D || !gridIndependent3D) 
		throw	new Exception(this,"HNCFreeEnergyFactory::createFreeEnergy : invalid class of argument");

//	Solution3DRISMK *betaUlong = m_noBetaU ?  NULL : gridDependent3D->getBetaUlong();

	return new HNCFreeEnergy3DRISM(
			gridDependent3D->getClosure(), //Closure3DRISM *closure,
	//		betaUlong,//Solution3DRISMK *betaUlongPotK,
			m_solutionFactory,//SolutionFactory3DRISMR *solutionFactory,
			gridIndependent3D->getSiteDensities()->getDensity(),//Real *densities, //[Bohr^-3]
			gridIndependent3D->getSiteMultiplicities()->getSiteMultiplicities(), 	// Integer *multiplicities
			gridIndependent3D->getKBT()//Real kBT	//[Hartree]
		);
}	
