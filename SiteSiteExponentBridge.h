#ifndef SiteSiteExponentBridge_h
#define SiteSiteExponentBridge_h

#include "Settings.h"
#include "SiteSitePotential.h"

#include "SigmaEpsilonTable.h"
#include "FirstPeakStartTable.h" // table there beggining of the first

//  h = exp( -beta*U + h-c +B) -1
// B = -epsilon12 * exp(-a(r-r0) + C sigma_solute/sigma_solvent )
//
// r0 is such, that exp(-beta*U^LJ(r0)) = 10^-6 (U(r0) = 13.8 kBT )
//
// another variant: r0 = kmax*r_max, where r_max 


// because we build not b, but potential we should return -kT*B:
//  c = exp(-beta*(U-kT*B)+...) = exp(-beta*U + B)


class SiteSiteExponentBridge : public SiteSitePotential
{
protected:
	Real *m_soluteSigma;
	Real *m_solventSigma;
	SigmaEpsilonTable *m_sigmaEpsilonTable;
	FirstPeakStartTable *m_firstPeakStartTable;

	Real m_a,m_C,m_kmax;
	Real m_kBT;

public:
	SiteSiteExponentBridge(	Real *soluteSigma,
				Real *solventSigma,
				SigmaEpsilonTable *sigmaEpsilonTable,
				FirstPeakStartTable *firstPeakStartTable,
				Real a,
				Real C,
				Real kmax,
				Real kBT
				)
	{
		m_soluteSigma = soluteSigma;
		m_solventSigma = solventSigma;
		m_firstPeakStartTable = firstPeakStartTable;
		m_sigmaEpsilonTable = sigmaEpsilonTable;
		m_a = a;
		m_C = C;
		m_kmax = kmax;
		m_kBT = kBT;
	}


	virtual Real calculatePotential(Integer soluteSite,Integer solventSite,Real R)
	{

		Real r0;

		if(m_kmax>0)
			r0 = m_firstPeakStartTable->getMaxPos(soluteSite,solventSite) * m_kmax;
		else
			r0 =  m_firstPeakStartTable->getStartPos(soluteSite,solventSite);

		Real sigma11 = m_soluteSigma[soluteSite];
		Real sigma22 = m_solventSigma[solventSite];
		Real epsilon12 = m_sigmaEpsilonTable->getEpsilon(soluteSite,solventSite);

		Real B = m_kBT * epsilon12/m_kBT *  exp( -m_a*(R-r0 )+m_C*(sigma11/sigma22) ); 

		return B;
	}

	virtual Integer getNumSoluteSites() 
	{
		return m_firstPeakStartTable->getNumSoluteSites();
	}
	virtual Integer getNumSolventSites()
	{
		return m_firstPeakStartTable->getNumSolventSites();
	}
};


#endif
