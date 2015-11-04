#ifndef SiteSitePotentialSum_h
#define SiteSitePotentialSum_h

#include "SiteSitePotential.h"

#include <vector>

class SiteSitePotentialSum : public SiteSitePotential
{
protected:

	std::vector<SiteSitePotential *>  m_summands;
	Integer m_numSoluteSites;
	Integer m_numSolventSites;

public:
	SiteSitePotentialSum()
	{
		m_numSoluteSites = m_numSolventSites = 0;
	}
	
	SiteSitePotentialSum(	SiteSitePotential *a,
				SiteSitePotential *b)
	{
		addSummand(a);
		addSummand(b);
	}

	SiteSitePotentialSum(	SiteSitePotential *a,
				SiteSitePotential *b,
				SiteSitePotential *c)
	{
		addSummand(a);
		addSummand(b);
		addSummand(c);
	}

	SiteSitePotentialSum(	SiteSitePotential *a,
				SiteSitePotential *b,
				SiteSitePotential *c,
				SiteSitePotential *d)
	{
		addSummand(a);
		addSummand(b);
		addSummand(c);
		addSummand(d);
	}

	void addSummand(SiteSitePotential *x);
	Real calculatePotential(Integer soluteSite,Integer solventSite,Real R);

	Integer getNumSoluteSites()
	{
		return m_numSoluteSites;
	}

	Integer getNumSolventSites()
	{
		return m_numSolventSites;
	}	

};

#endif
