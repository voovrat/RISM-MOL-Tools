#include "SiteSitePotentialSum.h"

#include "Exception.h"

void SiteSitePotentialSum::addSummand(SiteSitePotential *x)
{
	if(!m_summands.empty())
	{
		SiteSitePotential *first = *m_summands.begin();

		if(	m_numSoluteSites != x->getNumSoluteSites() ||
			m_numSolventSites != x->getNumSolventSites()
		)
		throw new Exception(this,"addSummand with incomplatiple number of sites");	

	}
	else
	{
		m_numSoluteSites = x->getNumSoluteSites();
		m_numSolventSites = x->getNumSolventSites();
	}


	m_summands.push_back(x);
}

Real SiteSitePotentialSum::calculatePotential(Integer soluteSite,Integer solventSite,Real R)
{
	Real S=0;
	std::vector<SiteSitePotential *>::iterator it;

	for(it=m_summands.begin(); it!=m_summands.end(); it++)
	{
		S=S+(*it)->calculatePotential(soluteSite,solventSite, R);
	}
	
	return S;
}


