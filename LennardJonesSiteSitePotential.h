#ifndef LennardJonesSiteSitePotential_h
#define LennardJonesSiteSitePotential_h

#include "SiteSitePotential.h"

class SigmaEpsilonTable;

class LennardJonesSiteSitePotential : public SiteSitePotential
{
protected:

	SigmaEpsilonTable *m_sigmaEpsilonTable;

public:
	LennardJonesSiteSitePotential(SigmaEpsilonTable *sigmaEpsilonTable)
	{
		m_sigmaEpsilonTable = sigmaEpsilonTable;
	}

	virtual Real calculatePotential(Integer soluteSite,Integer solventSite,Real R);

	virtual Integer getNumSoluteSites();

	virtual Integer getNumSolventSites();

};

#endif
