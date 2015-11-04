#ifndef ShortCoulombSiteSitePotential_h
#define ShortCoulombSiteSitePotential_h

#include "UnaryFunction.h"

#include "SiteSitePotential.h"

class MoleculeCharges;

class ShortCoulombSiteSitePotential : public SiteSitePotential
{
protected:
	MoleculeCharges *m_soluteCharges;
	MoleculeCharges *m_solventCharges;
	Real m_erfCoefficient;

	//UnaryFunction<Real,Real> *m_erf;

public:

	ShortCoulombSiteSitePotential(
			MoleculeCharges *soluteCharges,
			MoleculeCharges *solventCharges,
			//UnaryFunction<Real,Real> *erf,
			Real erfCoefficient
			)
	{
		m_soluteCharges = soluteCharges;
		m_solventCharges = solventCharges;
		//m_erf = erf;
		m_erfCoefficient = erfCoefficient;
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
