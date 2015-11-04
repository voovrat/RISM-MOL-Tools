#ifndef GridIndependent3DRISM3_h
#define GridIndependent3DRISM3_h

#include "GridIndependentInterface3DRISM.h"

class MoleculeCoordinates;
class MoleculeLJParameters;
class MoleculeCharges;

class SiteMultiplicities;
class TabFunction;
class SiteSitePotential;
class SiteDensities;

class ClosureFactory3DRISM;
class OmegaData;

class MixingRules;

class GridIndex;
class SigmaEpsilonTable;

class GridIndependent3DRISM3 : public GridIndependentInterface3DRISM
{

protected:

	// Solute Data
	MoleculeCoordinates 	*m_soluteCoors;
	MoleculeLJParameters	*m_soluteLJParameters;
	MoleculeCharges 	*m_soluteCharges;

	// Solvent Data
	MoleculeLJParameters	*m_solventLJParameters;
	MoleculeCharges		*m_solventCharges;
	SiteMultiplicities	*m_siteMultiplicities;

	// Functions	
	//TabFunction	*m_erfFunction;

	// the format of Chi and Phi:
	// array of n(n+1)/2 values (for i,j pairs) + Index: array nxn pointers to the values of the first array
	// (here n - numberof solventSites)

	TabFunction	**m_rdfs;
	TabFunction	**m_analyticChi;
	TabFunction	***m_analyticChiIndex;
	Real		**m_analyticChiMultipliers;

	TabFunction	**m_phi;	// phi[i][j] = d3ifft( exp(-k^2/2t)/k^2 * chi[i][j]  )
	TabFunction	***m_phiIndex;	

	TabFunction 	**m_phiLJ;	// phiLJ[i][j] = d3ifft( d3fft(U_LJ_long) * chi[i][j] )
	TabFunction 	***m_phiLJIndex;// where U_LJ_long =    -1/r^6 		if r>R_cut
					//			-1/R_cut^6 	else 
					// LJ potential can be reconstructed by 4*epsilon_ij*sigma_ij^6 * U_LJ_long
		


	OmegaData *m_omega;

	SiteSitePotential	*m_ngSiteSitePotential; // in k space
//	SiteSitePotential	*m_longPotential;	// includes long coulomb and long LJ potentials (r space)

	SiteSitePotential	*m_ljSiteSitePotential;	
	SiteSitePotential	*m_shortCoulombSiteSitePotential;

	SiteSitePotential	*m_shortSiteSitePotential; // sum of two above potentials  	

	SiteDensities *m_siteDensities;	

	Real m_kBT;
	Integer m_nRDFs;
	Integer m_numSolventSites,m_numSoluteSites;
	Real m_ngCoeff;
	//void (*m_mixingRules)(Real,Real,Real,Real,Real*,Real*);
	MixingRules *m_mixingRules;
	ClosureFactory3DRISM *m_closureFactory;

	GridIndex *m_gridDependentDataIndex;

	Real m_exponentBridgeA;
	Real m_exponentBridgeC;	
	Real m_exponentBridgeKmax;
	Integer m_useExponentBridge;


	Real m_ljPotentialCutoff;
	Integer m_useLJCorrection;

	SigmaEpsilonTable *m_sigmaEpsilonTable;

public:

	GridIndependent3DRISM3();

	virtual void init(	const char *soluteFname,
				const char *soluteDistanceUnits,
				const char *soluteEnergyUnits,

				const char *solventFname,
				const char *solventDistanceUnits,
				const char *solventEnergyUnits,
				const char *solventDensityDistanceUnits,

				const char *solventRdfFname,
				const char *solventRdfUnits,

				const char *omegaFname,
				const char *omegaDistanceUnits,			

				Real kBT,// Hartree
				Real ngCoeff,
				MixingRules *mixingRules,
				ClosureFactory3DRISM *closureFactory,
		
				Integer useExponentBridge = 0,	
				Real exponentBridgeA = 0,
				Real exponentBridgeC = 0,
				Real exponentBridgeKmax =0,
				Real ljPotentialCutoff = 0,
				Integer useLJCorrection = 0
		);
	

	virtual void unInit();

	virtual ~GridIndependent3DRISM3()
	{
		unInit();
	}

	void initGridIndex();
	
	virtual void loadSolute(
			const char *soluteFname,
			const char *distanceUnits,
			const char *energyUnits
		);

	virtual void loadSolvent(
			const char *solventFname,
			const char *distanceUnits,
			const char *energyUnits,
			const char *densityDistanceUnits);


	//virtual void loadErf(const char *erfFname);
	virtual void loadSolventRDFs(	const char *rdfFname,
					const char *distanceUnits);

	virtual void loadOmega(	const char *omegaFname,
				const char *distanceUnits
				);

	virtual void buildPotentials();

	virtual void buildAnalyticChi();
	virtual void buildPhi();

	virtual void buildSigmaEpsilonTable();
	
	// indeed this functions does not create GridDependent data, but only 
	// find it in the GridIndex
	virtual GridDependentData *createGridDependent(Grid *);

	// this function really creates GridDependent
	virtual GridDependentData *reallyCreateGridDependent(Grid *);


	MoleculeCoordinates 	*getSoluteCoordinates()
	{
		return m_soluteCoors;
	}

	MoleculeLJParameters	*getSoluteLJParameters()
	{
		return m_soluteLJParameters;
	}

	MoleculeCharges 	*getSoluteCharges()
	{
		return m_soluteCharges;
	}

	// Solvent Data
	MoleculeLJParameters	*getSolventLJParameters()
	{	
		return m_solventLJParameters;
	}

	MoleculeCharges		*getSolventCharges()
	{	
		return m_solventCharges;
	}

	SiteMultiplicities	*getSiteMultiplicities()
	{	
		return m_siteMultiplicities;
	}

	// Functions	
	//TabFunction	*getErf()
	//{
	//	return m_erfFunction;
	//}

	TabFunction	**getSolventRDFs()
	{
		return m_rdfs;
	}

	TabFunction 	**getAnalyticChi()
	{
		return m_analyticChi;
	}

	TabFunction 	***getAnalyticChiIndex()
	{
		return m_analyticChiIndex;
	}

	Real **getAnalyticChiMultipliers()
	{
		return m_analyticChiMultipliers;
	}

	TabFunction	**getPhi()
	{
		return m_phi;
	}

	TabFunction	***getPhiIndex()
	{
		return m_phiIndex;
	}

	TabFunction	**getPhiLJ()
	{
		return m_phiLJ;
	}

	TabFunction	***getPhiLJIndex()
	{
		return m_phiLJIndex;
	}

	OmegaData * 	getOmegaData()
	{
		return m_omega;
	}

	SiteSitePotential	*getNgSiteSitePotential()
	{
		return m_ngSiteSitePotential;
	}

	SiteSitePotential	*getLJSiteSitePotential()
	{
		return m_ljSiteSitePotential;	
	}

	SiteSitePotential	*getShortCoulombSiteSitePotential()
	{
		return m_shortCoulombSiteSitePotential;
	}

	SiteSitePotential	*getShortSiteSitePotential()
	{
		return m_shortSiteSitePotential; // sum of two above potentials  	
	}

	SiteDensities *getSiteDensities()
	{
		return m_siteDensities;
	}
	
	Real getKBT()
	{
		return m_kBT;
	}

	SigmaEpsilonTable *getSigmaEpsilonTable()
	{
		return m_sigmaEpsilonTable;
	}
	
	Real getNgCoefficient()
	{
		return m_ngCoeff;
	}

	Real getLJCutoff()
	{
		return m_ljPotentialCutoff;
	}
};

#endif
