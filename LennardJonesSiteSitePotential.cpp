#include "LennardJonesSiteSitePotential.h"

#include "SigmaEpsilonTable.h"
#include "lennardJonesPotential.h"

Integer LennardJonesSiteSitePotential::getNumSoluteSites()
{
	return m_sigmaEpsilonTable->getNumSoluteSites();
}

Integer LennardJonesSiteSitePotential::getNumSolventSites()
{
	return m_sigmaEpsilonTable->getNumSolventSites();
}



Real LennardJonesSiteSitePotential::calculatePotential(
				Integer soluteSite,
				Integer solventSite,
				Real R
				)
{
	Real sigma12 = m_sigmaEpsilonTable->getSigma(soluteSite,solventSite);
	Real epsilon12 = m_sigmaEpsilonTable->getEpsilon(soluteSite,solventSite);

	return lennardJonesPotential(sigma12,epsilon12,R);
}


