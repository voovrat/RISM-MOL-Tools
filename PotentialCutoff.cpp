#include "PotentialCutoff.h"	
#include <stdlib.h>

PotentialCutoff::PotentialCutoff(SiteSitePotential *potential,
				 Real cutoffDistance)
{
	m_potential = potential;
	m_cutoffDistance = cutoffDistance;
	m_numSoluteSites = potential->getNumSoluteSites();
	m_numSolventSites = potential->getNumSolventSites();

	m_cutoffCorrections = (Real *)malloc( m_numSoluteSites * m_numSolventSites * sizeof(double));

	int soluteSite,solventSite;
	Real *ptr = m_cutoffCorrections;
	for(soluteSite=0;soluteSite<m_numSoluteSites;soluteSite++)
	for(solventSite=0;solventSite<m_numSolventSites;solventSite++)
	{
		*ptr = potential->calculatePotential(soluteSite, solventSite, cutoffDistance);
		ptr++;
	}

}

PotentialCutoff::~PotentialCutoff()
{
	free(m_cutoffCorrections);
}

Real PotentialCutoff::calculatePotential(
			Integer soluteSite,
			Integer solventSite,
			Real R)
{
	if(R>m_cutoffDistance)
	{
		 return 0;
	}
	else
	{
		Real U = m_potential->calculatePotential( soluteSite, solventSite, R);
		return U - m_cutoffCorrections[ soluteSite * m_numSolventSites + solventSite];
	
	}



}


