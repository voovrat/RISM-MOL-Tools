#ifndef SiteSitePotentialExp_h
#define SiteSitePotentialExp_h

#include "SiteSitePotential.h"

#include <math.h>

class SiteSitePotentialExp : public SiteSitePotential
{
protected:
	SiteSitePotential *m_subPotential;
	Real m_beta;

public:
	SiteSitePotentialExp( SiteSitePotential *subPotential,
				 Real beta
				)
	{
		m_subPotential = subPotential;
		m_beta = beta;
	}


	virtual Real calculatePotential(Integer soluteSite,Integer solventSite,Real R)
	{
		Real U = m_subPotential->calculatePotential(soluteSite,solventSite,R);
		return exp( -m_beta * U );
	}

	virtual Integer getNumSoluteSites() 
	{
		return m_subPotential->getNumSoluteSites();
	}
	virtual Integer getNumSolventSites()
	{
		return m_subPotential->getNumSolventSites();
	}

};

#endif


