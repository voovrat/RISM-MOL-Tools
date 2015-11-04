#include "buildAnalyticalTheta2.h"

#include <math.h>

#include "MoleculeCoordinates.h"
#include "MoleculeCharges.h"
#include "TabFunction.h"
#include "SiteMultiplicities.h"
#include "Solution3DRISMR.h"

#include "buildPotential.h"
#include "buildPotential2.h"

#include "Settings.h"

#include "SiteSitePotential.h"

#include "buildRDF4.h"
#include "SigmaEpsilonTable.h"

class ThetaSiteSitePotentialWithLJ : public SiteSitePotential 
{
protected:
	Real *m_qSolute;
	Real *m_qSolvent;
	
	Integer*m_siteMultiplicities;
	Real **m_chiMultipliers;
	TabFunction ***m_phiIndex;
	TabFunction ***m_phiLJIndex;

	SigmaEpsilonTable *m_sigmaEpsilonTable;

	Integer m_NsoluteSites,m_NsolventSites;

public:
	ThetaSiteSitePotentialWithLJ(
				Integer NsoluteSites,
				Integer NsolventSites,
				Real *q_solute,
				Real *q_solvent,
				Integer *siteMultiplicities,
				Real **chiMultipliers,
				TabFunction ***phiIndex,
				TabFunction ***phiLJIndex,
				SigmaEpsilonTable *sigmaEpsilonTable
				)
	{
		m_qSolute = q_solute;
		m_qSolvent = q_solvent;
		m_siteMultiplicities = siteMultiplicities;
		m_chiMultipliers = chiMultipliers;
		m_phiIndex = phiIndex;
		m_phiLJIndex = phiLJIndex;
		m_NsoluteSites = NsoluteSites;
		m_NsolventSites = NsolventSites;
		m_sigmaEpsilonTable = sigmaEpsilonTable;
	}


// \Theta_{\gamma} = \sum_s{ q_s * \sum_{\alpha} multiplicity[alpha] * chiMultipliers[alpha][gamma] * phi[alpha][gamma](r_s)  }
	virtual Real calculatePotential(Integer soluteSite,Integer solventSite,Real R)
	{
		Real q_s,q_alpha,mul,chiMul,phi_r_s,S;
		Integer alpha;
			
		S = 0;
		for(alpha=0; alpha<m_NsolventSites; alpha++)
		{

			q_s = m_qSolute[soluteSite];
			q_alpha = m_qSolvent[alpha];
			mul = m_siteMultiplicities[alpha];
			chiMul = m_chiMultipliers[alpha][solventSite];
			phi_r_s = (*m_phiIndex[alpha][solventSite])(R);

			S  = S + q_s * q_alpha * mul * chiMul * phi_r_s;

			if(m_phiLJIndex)
			{
				Real sigma =
				 m_sigmaEpsilonTable->getSigma(	soluteSite,//Integer soluteSite,
								solventSite //Integer solventSite
							);

				Real sigma2 = sigma*sigma;
				Real sigma6 = sigma2*sigma2*sigma2;

				Real epsilon = 
				m_sigmaEpsilonTable->getEpsilon(soluteSite,//Integer soluteSite,
								solventSite//Integer solventSite
							);
				Real phiLJ_r_s = (*m_phiLJIndex[alpha][solventSite])(R);

				S = S + 4 * epsilon * sigma6 * mul * chiMul * phiLJ_r_s;

			}


		}//alpha
			
		return S;
	}

	virtual Integer getNumSoluteSites()
	{
		return m_NsoluteSites;
	}

	virtual Integer getNumSolventSites()
	{
		return m_NsolventSites;
	}
};



void buildAnalyticalTheta2(
			MoleculeCoordinates *soluteCoors,
			MoleculeCharges *soluteCharges,
			MoleculeCharges *solventCharges,
			SiteMultiplicities *siteMultiplicities,
			TabFunction  ***phiIndex,
			TabFunction  ***phiLJIndex,  // NULL if no LJ correction
			SigmaEpsilonTable *sigmaEpsilonTable,
			Real **chiMultipliers,
			Solution3DRISMR *theta			// out
		   )
{
// \Theta_{\gamma} = \sum_s{ q_s * \sum_{\alpha} multiplicity[alpha] * chiMultipliers[alpha][gamma] * phi[alpha][gamma](r_s)  }

Integer numSoluteSites = soluteCoors->getNumSites();
Integer numSolventSites = siteMultiplicities->getNumSites();


Integer *multiplicities = siteMultiplicities->getSiteMultiplicities();
Real *q_solute = soluteCharges->getCharge();
Real *q_solvent = solventCharges->getCharge();

ThetaSiteSitePotentialWithLJ thetaPotential	(
				numSoluteSites,		//Integer NsoluteSites,
				numSolventSites,	//Integer NsolventSites,
				q_solute,		//Real *q_solute,
				q_solvent,		//Real *q_solvent,
				multiplicities,		//Real *siteMultipliers,
				chiMultipliers,		//Real *chiMultipliers,
				phiIndex,		//TabFunction ***phiIndex
				phiLJIndex,		//TabFunction ***phiLJIndex
				sigmaEpsilonTable	//SigmaEpsilonTable *sigmaEpsilonTable
				);


#if USE_buildPotential
buildPotential (	// no averaging

	soluteCoors,		//MoleculeCoordinates *soluteCoors,
	&thetaPotential,	//SiteSitePotential *siteSitePotential,
	theta			//Solution3DRISMR *potential // output
);

#endif

#if USE_buildPotential2 || USE_buildPotential4



buildPotential(	//averaging
	soluteCoors,		//MoleculeCoordinates *soluteCoors,
	&thetaPotential,	//SiteSitePotential *siteSitePotential,
	theta			//Solution3DRISMR *potential // output
);

#endif

}
