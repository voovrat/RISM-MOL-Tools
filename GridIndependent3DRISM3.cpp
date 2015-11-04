#include "GridIndependent3DRISM3.h"

#include <stdlib.h>

#include "MoleculeCoordinates.h"
#include "MoleculeLJParameters.h"
#include "MoleculeCharges.h"

#include "SiteMultiplicities.h"
#include "TabFunction.h"
#include "SiteSitePotential.h"

#include "LennardJonesSiteSitePotential.h"
#include "SigmaEpsilonTable.h"
#include "ShortCoulombSiteSitePotential.h"
#include "NgSiteSitePotential.h"
#include "SiteSitePotentialSum.h"
#include "SiteDensities.h"

#include "readRISMMOLFile.h"
#include "readSolventDataFile2.h"
#include "readTabFunctionFromFile.h"
#include "readDoubleTable.h"
#include "doubleTable2TabFunctions.h"

#include "GridDependent3DRISM3.h"
#include "Exception.h"

#include "calculateBeta.h"
#include "Closure3DRISM.h"
#include "Grid3DRISM.h"

#include "OmegaData.h"
#include "getColumns.h"

#include "GridIndex.h"
#include "GridComparator3DRISM.h"
#include "GridDataFactory.h"

#include "SphericalFFT.h"
#include "Grid1DRISM.h"
#include "buildChi1DRISM.h"

#include "Pointer.h"

#include "FirstPeakStartTable.h"
#include "SiteSiteExponentBridge.h"

#include "PotentialCutoff.h"
#include "ArrayOperations.h"

#include "calculatePhiCoulomb2.h"
#include "calculatePhiLJ2.h"


class SpecialGridDependentDataFactory : public GridDataFactory
{
protected:

	GridIndependent3DRISM3 *m_gridIndependent3DRISM3;
public:
	SpecialGridDependentDataFactory(GridIndependent3DRISM3 *gridIndependent)
	{
		m_gridIndependent3DRISM3 = gridIndependent;
	}

	virtual Object *createData(Grid *grid)
	{
		return m_gridIndependent3DRISM3->reallyCreateGridDependent(grid);
	}
};



GridIndependent3DRISM3::GridIndependent3DRISM3()
{
	m_soluteCoors = NULL;
	m_soluteLJParameters = NULL;
	m_soluteCharges = NULL;

	// Solvent Data
	m_solventLJParameters = NULL;
	m_solventCharges = NULL;
	m_siteMultiplicities = NULL;

	// Functions	
	//m_erfFunction = NULL;
	m_rdfs = NULL; 
	m_analyticChi = NULL;
	m_analyticChiMultipliers = NULL;
	m_analyticChiIndex = NULL;

	m_phi = NULL;
	m_phiIndex = NULL;

	m_phiLJ = NULL;
	m_phiLJIndex = NULL;

	m_ngSiteSitePotential = NULL;
//	m_longPotential = NULL;

	m_ljSiteSitePotential = NULL;	
	m_shortCoulombSiteSitePotential = NULL;

	m_shortSiteSitePotential = NULL; // sum of two above potentials  
	m_siteDensities = NULL;

	m_omega = NULL;

	m_kBT=0;
	m_ngCoeff = 0;
	
	m_ngSiteSitePotential = NULL;

	m_ljSiteSitePotential = NULL;
	m_shortCoulombSiteSitePotential = NULL;

	m_shortSiteSitePotential =NULL; // sum of two above potentials  
	m_omega = NULL;

	m_gridDependentDataIndex = NULL;



}

void GridIndependent3DRISM3::unInit()
{

	NULL_DELETE(m_soluteCoors);
	NULL_DELETE(m_soluteLJParameters);
	NULL_DELETE(m_soluteCharges );

	// Solvent Data
	NULL_DELETE(m_solventLJParameters );
	NULL_DELETE(m_solventCharges );
	NULL_DELETE(m_siteMultiplicities );

	// Functions	
	//NULL_DELETE(m_erfFunction);

	if(m_rdfs)
	{	Integer i;
		for(i=0;i<m_nRDFs;i++)
			NULL_DELETE(m_rdfs[i]);

	delete [] m_rdfs;
	}

	if(m_analyticChi)
	{	Integer i;
		for(i=0;i<m_nRDFs;i++)
			NULL_DELETE(m_analyticChi[i]);

	delete [] m_analyticChi;
	}

	if(m_analyticChiIndex)
	{
		Integer i;
		for(i=0;i<m_numSolventSites;i++)
			free(m_analyticChiIndex[i]);

		free(m_analyticChiIndex);
		m_analyticChiIndex = NULL;
	}

	if(m_analyticChiMultipliers)
	{
		Integer i;
		for(i=0;i<m_numSolventSites; i++)
			free(m_analyticChiMultipliers[i]);

		free(m_analyticChiMultipliers);
		m_analyticChiMultipliers = NULL;
	}

	if(m_phi)
	{	Integer i;
		for(i=0;i<m_nRDFs;i++)
			NULL_DELETE(m_phi[i]);

	delete [] m_phi;
	m_phi = NULL;
	}

	if(m_phiIndex)
	{
		Integer i;
		for(i=0;i<m_numSolventSites;i++)
			free(m_phiIndex[i]);

		free(m_phiIndex);
		m_phiIndex = NULL;
	}

	if(m_phiLJ)
	{	Integer i;
		for(i=0;i<m_nRDFs;i++)
			NULL_DELETE(m_phiLJ[i]);

	delete [] m_phiLJ;
	m_phiLJ = NULL;
	}

	if(m_phiLJIndex)
	{
		Integer i;
		for(i=0;i<m_numSolventSites;i++)
			free(m_phiLJIndex[i]);

		free(m_phiLJIndex);
		m_phiLJIndex = NULL;
	}

//	NULL_DELETE(m_chi );

	NULL_DELETE(m_ngSiteSitePotential );
//	NULL_DELETE(m_longPotential);
	NULL_DELETE(m_ljSiteSitePotential );	
	NULL_DELETE(m_shortCoulombSiteSitePotential );

	NULL_DELETE(m_shortSiteSitePotential ); // sum of two above potentials  
	NULL_DELETE(m_omega);

	NULL_DELETE(m_gridDependentDataIndex);
}


void GridIndependent3DRISM3::init(const char *soluteFname,
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

				Integer useExponentBridge,
				Real exponentBridgeA,
				Real exponentBridgeC,
				Real exponentBridgeKmax,
				Real ljPotentialCutoff,
				Integer useLJCorrection
		)
{
	
	m_kBT = kBT;
	m_ngCoeff = ngCoeff;
	m_mixingRules = mixingRules;
	m_closureFactory = closureFactory;

	m_useExponentBridge = useExponentBridge;
	m_exponentBridgeA = exponentBridgeA;
	m_exponentBridgeC = exponentBridgeC;
	m_exponentBridgeKmax = exponentBridgeKmax;

	m_ljPotentialCutoff = ljPotentialCutoff;
	m_useLJCorrection = useLJCorrection;
	if(m_ljPotentialCutoff<=0) m_useLJCorrection = 0;

	loadSolute(soluteFname,soluteDistanceUnits,soluteEnergyUnits);
	loadSolvent(	solventFname,			//const char *solventFname,
			solventDistanceUnits,		//const char *distanceUnits,
			solventEnergyUnits,		//const char *energyUnits,
			solventDensityDistanceUnits	//const char *densityDistanceUnits
	);
	//loadErf(erfFname);
	loadSolventRDFs(solventRdfFname,solventRdfUnits);
	loadOmega(omegaFname,omegaDistanceUnits);

	buildSigmaEpsilonTable();
	buildPotentials();

	initGridIndex();

	buildAnalyticChi();
	buildPhi();



}

void GridIndependent3DRISM3::buildSigmaEpsilonTable()
{
	Integer numSolventSites = m_solventCharges->getNumSites();

	m_sigmaEpsilonTable = new SigmaEpsilonTable
					(
					m_soluteCoors->getNumSites(),
					numSolventSites);

	m_sigmaEpsilonTable->fill(	
		m_soluteLJParameters,		//MoleculeLJParameters *soluteParameters,
		m_solventLJParameters,		//MoleculeLJParameters *solventParameters,
		m_mixingRules	//  MixingRules *
	);



}


void GridIndependent3DRISM3::initGridIndex()
{

SpecialGridDependentDataFactory *gridDependentFactory = new SpecialGridDependentDataFactory(this);

GridComparator3DRISM *gridComparator3DRISM = GridComparator3DRISM::getInstance();

m_gridDependentDataIndex = new GridIndex(gridDependentFactory, //GridDataFactory *gridDataFactory,
			gridComparator3DRISM//Comparator<Grid> *gridComparator
	);

m_gridDependentDataIndex->addToDeleteList(gridDependentFactory);

}
	
void GridIndependent3DRISM3::loadSolute(	const char *soluteFname,
					const char *distanceUnits,
					const char *energyUnits)
{
	if(!m_soluteCoors)
		m_soluteCoors = new MoleculeCoordinates();

	if(!m_soluteLJParameters)
		m_soluteLJParameters = new MoleculeLJParameters();
	
	if(!m_soluteCharges)
		m_soluteCharges = new MoleculeCharges();

	readRISMMOLFile(
		soluteFname,		//const char *fname,
		distanceUnits,		//const char *distanceUnits,
		energyUnits,		//const char *energyUnits,
		m_soluteCoors,		//MoleculeCoordinates *coors, //output argument
		m_soluteLJParameters,	//MoleculeLJParameters *LJ,//output argument
		m_soluteCharges		//MoleculeCharges *charge//output argument
	);

	m_numSoluteSites = m_soluteCoors->getNumSites();

}

void GridIndependent3DRISM3::loadSolvent(
			const char *solventFname,
			const char *distanceUnits,
			const char *energyUnits,
			const char *densityDistanceUnits)
{


	if(!m_solventLJParameters)
		m_solventLJParameters = new MoleculeLJParameters();

	if(!m_solventCharges)
		m_solventCharges = new MoleculeCharges();

	if(!m_siteMultiplicities)
		m_siteMultiplicities = new SiteMultiplicities();

	if(!m_siteDensities)
		m_siteDensities = new SiteDensities();

readSolventDataFile2(
		solventFname,	//const char *fname,
		distanceUnits,	//const char *distanceUnits,
		energyUnits,	//const char *energyUnits,
		densityDistanceUnits,	//const char *densityDistanceUnits,
		m_solventLJParameters,	//MoleculeLJParameters *LJ,//output argument
		m_solventCharges,	//MoleculeCharges *charges,//output argument
		m_siteMultiplicities,	//SiteMultiplicities *siteMultiplicities, // output argument
		m_siteDensities		//SiteDensities *siteDensities	//output argument
	);

	m_numSolventSites = m_siteMultiplicities->getNumSites();

}

/*
void GridIndependent3DRISM3::loadErf(const char *erfFname)
{
	if(!m_erfFunction)
		m_erfFunction = new TabFunction();

	readTabFunctionFromFile(erfFname,m_erfFunction);
}
*/

void GridIndependent3DRISM3::loadSolventRDFs(	const char *rdfFname,
						const char *distanceUnits)
{

	Real *data;
	Integer i,nlin,ncol;

	readDoubleTable(rdfFname,	//	const char *fname,
			&nlin,	//Integer *Nrow,	//out
			&ncol,	//Integer *Ncol,	//out
			&data 	//Real **result //out, will be allocated
			);

	m_nRDFs = ncol-1;

	m_rdfs = new TabFunction*[m_nRDFs]; // first column - x

	for(i=0;i<ncol-1;i++)
		m_rdfs[i] = new TabFunction();

	Real unitKoef = Units::distanceUnits()->unit2unit(distanceUnits,"Bohr");

	doubleTable2TabFunctions(
			data,	//Real *data,	// line-by-line
			nlin,	//Integer nlin,			
			ncol,	//Integer ncol,
			m_rdfs,	//TabFunction **tabFunctions	//out. will NOT be allocated
			unitKoef
			);

	free(data);
}


void   GridIndependent3DRISM3::buildAnalyticChi()
{
	Integer i;

	Integer N = m_rdfs[0]->getTabSize();
	Real dR = m_rdfs[0]->getTabStep();

	Grid1DRISM grid(N,dR);
	Real dk = grid.getDK();


	m_analyticChi = new TabFunction*[m_nRDFs];
	for(i=0;i<m_nRDFs;i++)
	{
		m_analyticChi[i] = new TabFunction();
		Real *data = (Real *)malloc( N * sizeof(Real) );
		
		m_analyticChi[i]->init( data,	//Real *tab,
					N,	//Integer N,
					dk,	//Real x0,
					dk	//Real dx
					);

		m_analyticChi[i]->addToDeleteList(new Pointer(data));
	}

	m_analyticChiIndex = (TabFunction ***)malloc( m_numSolventSites * sizeof(TabFunction **) );
	for(i=0; i<m_numSolventSites; i++)
	{
		m_analyticChiIndex[i] = (TabFunction **)malloc( m_numSolventSites * sizeof(TabFunction*) );
	}

	m_analyticChiMultipliers = (Real **)malloc( m_numSolventSites * sizeof(Real *) );
	for(i=0; i <m_numSolventSites; i++)
		m_analyticChiMultipliers[i] = (Real *)malloc( m_numSolventSites * sizeof(Real));

	buildChi1DRISM(
		m_rdfs,			//TabFunction **rdfs,// array size= numSolventSites*(numSolventSites-1)/2
				  	// elements g11, g12.. g1N, g22,...g2N... gNN
		m_numSolventSites,	//Integer numSolventSites,
		m_omega,		//OmegaData *omega,
		m_siteDensities->getDensity(),	//Real *densities,	//in Bohr^-3
		m_analyticChi,			//TabFunction **chi,	//out, coresponds to chi
		m_analyticChiIndex,		//TabFunction ***chiIndex,	//out, numSolventSites*numSolventSites array
						// chiIndex[i][j] contains chi[i][j]
		m_analyticChiMultipliers	//Real **chiMultipliers // out
		);

}


// in k space: 	phi[i][j] = chi[i][j] *  (-beta) * 4 * M_PI  / k2 *exp(-k2/4/ t2); 
//		phiLJ[i][j] = chi[i][j] * d3fft ( -1/r^6 )
void GridIndependent3DRISM3::buildPhi()
{
	Integer i,j;
	
	Integer N = m_rdfs[0]->getTabSize();
	Real dR = m_rdfs[0]->getTabStep();

	Grid1DRISM grid(N,dR);
	Real dk = grid.getDK();

	m_phi = new TabFunction*[m_nRDFs];
	m_phiLJ = new TabFunction*[m_nRDFs];

	for(i=0;i<m_nRDFs;i++)
	{

		// Coulomb Long
		m_phi[i] = new TabFunction();
		Real *data = (Real *)malloc( N * sizeof(Real) );
		
		m_phi[i]->init( data,	//Real *tab,
				N,	//Integer N,
				dR,	//Real x0,
				dR	//Real dx
				);

		m_phi[i]->addToDeleteList(new Pointer(data));

		// LJ Long 
		m_phiLJ[i] = new TabFunction();
		Real *dataLJ = (Real *)malloc( N * sizeof(Real) );
	
		m_phiLJ[i]->init( dataLJ,	//Real *tab,
				N,	//Integer N,
				dR,	//Real x0,
				dR	//Real dx
				);

		m_phiLJ[i]->addToDeleteList(new Pointer(dataLJ));
	}

	// Creating arrays for Coulomb_long and LJ_long indeces

	m_phiIndex = (TabFunction ***)malloc( m_numSolventSites * sizeof(TabFunction **) );
	m_phiLJIndex = (TabFunction ***)malloc( m_numSolventSites * sizeof(TabFunction **) );

	for(i=0; i<m_numSolventSites; i++)
	{
		m_phiIndex[i] = (TabFunction **)malloc( m_numSolventSites * sizeof(TabFunction*) );
		m_phiLJIndex[i] = (TabFunction **)malloc( m_numSolventSites * sizeof(TabFunction*) );
	}

	// ----------  Calculating Phi a Coulomb Part (Phi):
	// 		1/k^2 exp(-k^2/4t^2) * chi[i][j]

	calculatePhiCoulomb2(	&grid,		//Grid1DRISM *grid,
				getKBT(),	//Real	KBT,
				m_analyticChiIndex,	//TabFunction ***analyticChiIndex,
				m_analyticChiMultipliers,
				m_ngCoeff,	//Real ngCoeff,
				m_numSolventSites,	//Integer numSolventSites,
				m_phi,		//TabFunction **phi,	//out
				m_phiIndex	//TabFunction ***phiIndex //out
			);

	// Calculation PhiLJ d3ifft2( d3fft(U_lj_long) * chi[i][j] )
		
	if(m_useLJCorrection && m_ljPotentialCutoff>0)
	{
		calculatePhiLJ2(	&grid,			//Grid1DRISM *grid,
				getKBT(),		//Real KBT
				m_analyticChiIndex,	//TabFunction ***analyticChiIndex,
				m_analyticChiMultipliers,
				m_ljPotentialCutoff,	//Real ljPotentialCutoff,	
				m_numSolventSites,	//Integer numSolventSites,
				m_phiLJ,		//TabFunction **phi,	//out
				m_phiLJIndex		//TabFunction ***phiIndex //out
			);

	}	
	else
	{	
		m_phiLJ = NULL;
		m_phiLJIndex = NULL;
		m_useLJCorrection = 0;
	}

}



void GridIndependent3DRISM3::loadOmega(	const char *omegaFname,
					const char *distanceUnits
					)
{
	Real *data;
	Integer i,nlin,ncol;

	readDoubleTable(omegaFname,	//	const char *fname,
			&nlin,		//Integer *Nrow,	//out
			&ncol,		//Integer *Ncol,	//out
			&data 		//Real **result //out, will be allocated
			);

	

	NULL_DELETE(m_omega);

	m_omega = new OmegaData();

	m_omega->allocData(nlin);

	Real *columns[3];

	getColumns(	data,	//Real *matrix, 
			nlin,	//Integer nlin,
			ncol,	//Integer ncol,
			m_omega->getRawData(),	///Real *columnData, // out, shuld be pre-allocated of size nlin*ncol*sizeof(Real)
			columns			//Real **columns    // out, should be pre-allocated of size ncol*sizeof(Real *)
		);

	free(data);

	Real kDistance = Units::distanceUnits()->unit2unit(distanceUnits,"Bohr");

	for(i=0;i<m_omega->getNumOmega();i++)
	{
		m_omega->getOmegaPosition()[i] *= kDistance;
	}


}

void GridIndependent3DRISM3::buildPotentials()
{
	m_ngSiteSitePotential = new NgSiteSitePotential(m_soluteCharges, 
						m_solventCharges, 
						m_ngCoeff);	


	Integer numSolventSites = m_solventCharges->getNumSites();

	SigmaEpsilonTable *sigmaEpsilonTable = m_sigmaEpsilonTable;
//new SigmaEpsilonTable
//					(
//					m_soluteCoors->getNumSites(),
//					numSolventSites);

//	sigmaEpsilonTable->fill(	
//		m_soluteLJParameters,		//MoleculeLJParameters *soluteParameters,
//		m_solventLJParameters,		//MoleculeLJParameters *solventParameters,
//		m_mixingRules	//  MixingRules *
//	);

	SiteSitePotential *ljSiteSitePotential00 = new LennardJonesSiteSitePotential(sigmaEpsilonTable);
	ljSiteSitePotential00->addToDeleteList(sigmaEpsilonTable);

	SiteSitePotential *ljSiteSitePotential0;

	if(m_ljPotentialCutoff>0)
	{
		ljSiteSitePotential0 = 
			new PotentialCutoff(
				ljSiteSitePotential00,	//SiteSitePotential *potential, 
				m_ljPotentialCutoff	//Real cutoffDistance
				);
		ljSiteSitePotential0->addToDeleteList(ljSiteSitePotential00);
	}
	else ljSiteSitePotential0 = ljSiteSitePotential00;


//#if USE_EXPONENT_BRIDGE

if(m_useExponentBridge)
{	FirstPeakStartTable *firstPeakTable = new FirstPeakStartTable();
	firstPeakTable->fill(
			ljSiteSitePotential0,		//SiteSitePotential *ljPotential,
			1/m_kBT			//Real beta,
			//Real treshold = 1e-6,
			//Real dr = 0.1,
			//Real Rmax = 100
		);
	ljSiteSitePotential0->addToDeleteList(firstPeakTable);

	
	SiteSiteExponentBridge *bridge = new SiteSiteExponentBridge(	
				getSoluteLJParameters()->getSigma(),	//Real *soluteSigma,
				getSolventLJParameters()->getSigma(),	//Real *solventSigma,
				sigmaEpsilonTable,			//SigmaEpsilonTable*
				firstPeakTable,				//FirstPeakStartTable *firstPeakStartTable,
				m_exponentBridgeA,			//Real a,
				m_exponentBridgeC,			//Real C,
				m_exponentBridgeKmax,			//Real kmax
				m_kBT
				);


	m_ljSiteSitePotential = new SiteSitePotentialSum(
					ljSiteSitePotential0,
					bridge
					);
	m_ljSiteSitePotential->addToDeleteList(ljSiteSitePotential0);
	m_ljSiteSitePotential->addToDeleteList(bridge);

#if DEBUG_BRIDGE
	bridge->saveToFile(	"bridge.txt",	//const char *fname,
				0.1,		//Real dr,
				30		//Real Rmax
			);

	ljSiteSitePotential0->saveToFile("lj0.txt",	//const char *fname,
				0.1,		//Real dr,
				30		//Real Rmax
			);

	m_ljSiteSitePotential->saveToFile("ljFull.txt",0.1,30);


#endif 
	
}
else
{
	m_ljSiteSitePotential = ljSiteSitePotential0;
}	
//#else


	

//#endif

	m_shortCoulombSiteSitePotential = new ShortCoulombSiteSitePotential(
			m_soluteCharges, 	//MoleculeCharges *soluteCharges,
			m_solventCharges,	//MoleculeCharges *solventCharges,
		//	m_erfFunction,		//UnaryFunction<Real,Real> *erf,
			m_ngCoeff		//Real erfCoefficient
			);

	m_shortSiteSitePotential = new SiteSitePotentialSum(
					m_ljSiteSitePotential,
					m_shortCoulombSiteSitePotential);
}

	// indeed this functions does not create GridDependent data, but only 
	// find it in the GridIndex
GridDependentData *GridIndependent3DRISM3::createGridDependent(Grid *grid)
{
	GridDependentData *gridDependent = (GridDependentData *)m_gridDependentDataIndex->findData(grid);
	gridDependent->retain(); // Nobody can delete it!!!. When calling NULL_DELETE nothing happens
	return gridDependent;
}


GridDependentData *GridIndependent3DRISM3::reallyCreateGridDependent(Grid *grid)
{
	Grid3DRISM *g3d = dynamic_cast<Grid3DRISM *>(grid);

	if(!g3d)
		throw new Exception(this,"GridIndependent3DRISM::createGridDependent: invalid grid class");
		GridDependent3DRISM3 *gridDependent= 
			new GridDependent3DRISM3(
				this,			//GridIndependentData *gridIndependent,
				g3d,			//Grid3DRISM *grid,
				1/m_kBT,		//Real beta,
				m_siteDensities,	//SiteDensities *siteDensities,
				m_soluteCoors,		//MoleculeCoordinates *soluteCoors,
				
				m_soluteCharges,	//MoleculeCharges *soluteCharges,
				m_solventCharges,	//MoleculeCharges *solventCharges,
				m_phiIndex,		//TabFunction ***phiIndex,
				m_analyticChiMultipliers,//Real **analyticChiMultipliers,

				m_shortSiteSitePotential,	//SiteSitePotential *shortPotential,
				//SiteSitePotential *longPotentialK,
				m_rdfs,			//TabFunction **solventRDFTab,
				m_omega,		//OmegaData *omegaData, 
				m_siteMultiplicities,	//SiteMultiplicities *siteMultiplicities,
				m_closureFactory	//ClosureFactory3DRISM *closureFactory
				
			);
/*	GridDependent3DRISM2 *gridDependent=
			new GridDependent3DRISM2(	
				this,			//GridIndependentData *gridIndependent,
				g3d,			//Grid3DRISM *grid,
				1/m_kBT,		//Real beta,
				m_siteDensities,	//SiteDensities *siteDensities,
				m_soluteCoors,		//MoleculeCoordinates *soluteCoors,
				m_shortSiteSitePotential,//SiteSitePotential *shortPotential,
				m_ngSiteSitePotential,	//SiteSitePotential *longPotentialK,
				m_rdfs,			//TabFunction **solventRDFTab,
				m_omega,		//OmegaData *omegaData, 
				m_siteMultiplicities,	//SiteMultiplicities *siteMultiplicities,
				m_closureFactory	//ClosureFactory3DRISM *closureFactory
			);
*/
	
	return gridDependent;
}


