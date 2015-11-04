#include "LongSiteSitePotential.h"

#include "MoleculeCharges.h"
#include "Settings.h"
#include "ErfFunction.h"
#include "SigmaEpsilonTable.h"

Real LongSiteSitePotential::calculatePotential(
				Integer soluteSite,
				Integer solventSite,
				Real R)
{
	if(R<MIN_DISTANCE) R=MIN_DISTANCE;

	
	/* COULOMB */
	Real q1 = m_soluteCharges->getCharge()[soluteSite];
	Real q2 = m_solventCharges->getCharge()[solventSite];


	ErfFunction *erf = ErfFunction::getInstance();

	Real U_C = q1*q2*((*erf)(m_erfCoefficient*R))/R;

	Real sigma = m_sigmaEpsilonTable->getSigma(soluteSite,solventSite);
	Real epsilon = m_sigmaEpsilonTable->getEpsilon(soluteSite,solventSite);

 	/* LJ */
	Real r0 = (R<m_ljcutoff) ? m_ljcutoff : R;

	Real sigmaDivR = sigma/r0;
	Real sigmaDivR3 = sigmaDivR*sigmaDivR*sigmaDivR;
	Real sigmaDivR6 = sigmaDivR3*sigmaDivR3;

	Real U_LJ = - 4*epsilon*sigmaDivR6;
	

	return U_C + U_LJ;

}
