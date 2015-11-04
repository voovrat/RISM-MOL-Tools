#include "ShortCoulombSiteSitePotential.h"

#include "MoleculeCharges.h"
#include "Settings.h"
#include "ErfFunction.h"

Real ShortCoulombSiteSitePotential::calculatePotential(
				Integer soluteSite,
				Integer solventSite,
				Real R)
{

	Real q1 = m_soluteCharges->getCharge()[soluteSite];
	Real q2 = m_solventCharges->getCharge()[solventSite];

	if(R<MIN_DISTANCE) R=MIN_DISTANCE;

	ErfFunction *erf = ErfFunction::getInstance();

	return q1*q2*(1-(*erf)(m_erfCoefficient*R))/R;

}
