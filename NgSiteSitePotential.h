#ifndef NgSiteSitePotential_h
#define NgSiteSitePotential_h

//#include "UnaryFunction.h"

// Attention: Potential is calculated in the Fourier space

#include "SiteSitePotential.h"
#include "MoleculeCharges.h"

//class MoleculeCharges;

class NgSiteSitePotential : public SiteSitePotential
{
protected:
	MoleculeCharges *m_soluteCharges;
	MoleculeCharges *m_solventCharges;
	Real m_erfCoefficient;

//	UnaryFunction<Real,Real> *m_erf;

public:

	static Real calculateNgPotential( 	
					Real q1, 
					Real q2, 
					Real erfCoefficient, 
					Real k
					);

	NgSiteSitePotential(
			MoleculeCharges *soluteCharges,
			MoleculeCharges *solventCharges,
//			UnaryFunction<Real,Real> *erf,
			Real erfCoefficient
			)
	{
		m_soluteCharges = soluteCharges;
		m_solventCharges = solventCharges;
		//m_erf = erf;
		m_erfCoefficient = erfCoefficient;
	}

	Real calculatePotential(Integer soluteSite,Integer solventSite,Real k);

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
