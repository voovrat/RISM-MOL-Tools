#ifndef LongSiteSitePotential_h
#define LongSiteSitePotential_h

#include "UnaryFunction.h"

#include "SiteSitePotential.h"
#include "MoleculeCharges.h"

// U_long = q1q2/r erf(tr) + U_LJ_long


class MoleculeCharges;
class SigmaEpsilonTable;

class LongSiteSitePotential : public SiteSitePotential
{
protected:
	MoleculeCharges *m_soluteCharges;
	MoleculeCharges *m_solventCharges;
	Real m_erfCoefficient;

	SigmaEpsilonTable *m_sigmaEpsilonTable;
	Real m_ljcutoff;
	//UnaryFunction<Real,Real> *m_erf;

public:

	LongSiteSitePotential(
			MoleculeCharges *soluteCharges,
			MoleculeCharges *solventCharges,
			//UnaryFunction<Real,Real> *erf,
			Real erfCoefficient,
			SigmaEpsilonTable *sigmaEpsilonTable,
			Real LJCutoff
			)
	{
		m_soluteCharges = soluteCharges;
		m_solventCharges = solventCharges;
		//m_erf = erf;
		m_erfCoefficient = erfCoefficient;

		m_sigmaEpsilonTable = sigmaEpsilonTable;
		m_ljcutoff = LJCutoff;
	}

	Real calculatePotential(Integer soluteSite,Integer solventSite,Real R);

	virtual Integer getNumSoluteSites()
	{
		return m_soluteCharges->getNumSites();
	}

	virtual Integer getNumSolventSites()
	{
		return m_solventCharges->getNumSites();
	}


};


#endif
