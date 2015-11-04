#include "GridDependent3DRISM3.h"

#include "Grid3DRISM.h"
#include "Solution3DRISMR.h"
#include "Solution3DRISMK.h"

#include "MoleculeCoordinates.h"
#include "SiteSitePotential.h"
#include "SiteMultiplicities.h"
#include "TabFunction.h"

#include "Closure3DRISM.h"

#include "buildChi3.h"
#include "buildChi4.h"
//#include "buildChi5.h"

#include "buildPotential.h"
#include "buildPotential2.h"
#include "buildPotential3.h"
#include "buildPotential4.h"

#include "calculateTheta2.h"
#include "SiteDensities.h"

#include "Settings.h"
#include "buildAnalyticalTheta2.h"

#include "SiteSitePotentialExp.h"
#include <math.h>

#include "writeDoubleArrayToFile.h"

#include "GridIndependent3DRISM3.h"

GridDependent3DRISM3::GridDependent3DRISM3(
				GridIndependentData *gridIndependent,
				Grid3DRISM *grid,
				Real beta,
				SiteDensities *siteDensities,
				MoleculeCoordinates *soluteCoors,
				
				MoleculeCharges *soluteCharges,
				MoleculeCharges *solventCharges,
				TabFunction ***phiIndex,
				Real **analyticChiMultipliers,

				SiteSitePotential *shortPotential,
				//SiteSitePotential *longPotentialK,
				TabFunction **solventRDFTab,
				OmegaData *omegaData, 
				SiteMultiplicities *siteMultiplicities,
				ClosureFactory3DRISM *closureFactory
			)	
: GridDependentInterface3DRISM(grid,gridIndependent)
{

#if DEBUG_LEAKS
	FILE *f=fopen("leaks.txt","r+");
	fseek(f,0,SEEK_END);
	fprintf(f,"CONSTRUCTOR  GridDependent3DRISM3::~GridDependent3DRISM3(): this=%p\n",this);
	fclose(f);
#endif

	m_numSolventSites = siteMultiplicities->getNumSites();
	m_beta = beta;
	m_chiMultipliers = NULL;

	initChi(solventRDFTab,	//TabFunction **solventRDFs,
		siteDensities,	//Real density,	
		omegaData	//OmegaData *omegaData
		);

	initShortPotential(	soluteCoors, 	//MoleculeCoordinates *soluteCoors,
				shortPotential	//SiteSitePotential *shortPotential
			  );

//	initTheta(	soluteCoors,		//MoleculeCoordinates *soluteCoors,
//			siteMultiplicities,	//SiteMultiplicities *siteMultiplicities, 
//			longPotentialK		//SiteSitePotential *longPotentialK
//		);
	initTheta(	soluteCoors,		//MoleculeCoordinates *soluteCoors,
			soluteCharges,		//MoleculeCharges *soluteCharges,
			solventCharges,		//MoleculeCharges *solventCharges,
			siteMultiplicities,	//SiteMultiplicities *siteMultiplicities, 
			phiIndex,		//TabFunction ***phiIndex,
		
			analyticChiMultipliers	//Real **analyticChiMultipliers,
//			SiteSitePotential *longPotentialK
		);



	initClosure( closureFactory);
}


GridDependent3DRISM3::~GridDependent3DRISM3()
{
Integer i;

#if DEBUG_LEAKS
	FILE *f=fopen("leaks.txt","r+");
	fseek(f,0,SEEK_END);
	fprintf(f,"DESTRUCTOR  GridDependent3DRISM3::~GridDependent3DRISM3(): this=%p\n",this);
	fclose(f);
#endif


if(m_chiIndex)
{
	for(i=0;i<m_numSolventSites;i++)
		delete [] m_chiIndex[i];

	delete [] m_chiIndex;
	m_chiIndex = NULL;
}

if(m_chi3D)
{
	for(i=0;i<m_numChi;i++)
		NULL_DELETE(m_chi3D[i]);

	delete [] m_chi3D;
	m_chi3D = NULL;
}

	NULL_DELETE(m_betaUshort);
	NULL_DELETE(m_theta);
	NULL_DELETE(m_closure);

	if(m_chiMultipliers)
	{
		Integer i;
		for(i=0;i<m_numSolventSites;i++)
		{
			free(m_chiMultipliers[i]);
		}
		free(m_chiMultipliers);
	m_chiMultipliers=NULL;

	}

//	NULL_DELETE(m_betaUlong)
}


void GridDependent3DRISM3::initChi(
		TabFunction **solventRDFs,
		SiteDensities *siteDensities,
		OmegaData *omegaData
		)
{
	Integer i;
	
	m_numChi = m_numSolventSites * (m_numSolventSites+1)/2;

	SolutionFactory3DRISMK chiFactory(1);

	m_chi3D = new Solution3DRISMK*[m_numChi];

	for(i=0;i<m_numChi;i++)
		m_chi3D[i] = (Solution3DRISMK *)chiFactory.createSolution(m_grid);

	m_chiIndex = new Solution3DRISMK**[m_numSolventSites];

	for(i=0;i<m_numSolventSites;i++)
		m_chiIndex[i] = new Solution3DRISMK*[m_numSolventSites];

	m_chiMultipliers = (Real **)malloc(m_numSolventSites*sizeof(Real*));
	for(i=0;i<m_numSolventSites;i++)
		m_chiMultipliers[i]=(Real*)malloc(m_numSolventSites*sizeof(Real));
#if USE_buildChi3
	buildChi3 (	// omega, RDFs - R space
#endif
#if USE_buildChi4
	buildChi4(    // omega RDFs - k space
#endif	
		solventRDFs,	//TabFunction **rdfs, g11, g12.. g1N, g22,...g2N... gNN
		m_numSolventSites,	//Integer numSolventSites,
		omegaData,		//OmegaData *omega,
		siteDensities->getDensity(),	//Real *density,	//in 	Bohr^-3		
		m_chi3D,	//Solution3DRISMK **chi3D,//out, coresponds to chi
		m_chiIndex,//Solution3DRISMK ***chiIndex	//out, chi[i][j]
		m_chiMultipliers
		);
#ifdef VIM_IS_STUPID
)
#endif
}


void GridDependent3DRISM3::initShortPotential(MoleculeCoordinates *soluteCoors,
					SiteSitePotential *shortPotential)
{
	SolutionFactory3DRISMR potFactory(m_numSolventSites);

	m_betaUshort = (Solution3DRISMR *)potFactory.createSolution(m_grid);


#if USE_buildPotential
printf("buildPotential...\n");
	buildPotential (
		soluteCoors,		//MoleculeCoordinates *soluteCoors,
		shortPotential,	//SiteSitePotential *siteSitePotential,
		m_betaUshort			//Solution3DRISMR *potential3D // output
	);
#endif


#if USE_buildPotential2

#if AVERAGE_EXP_POTENTIAL
printf("buildPotential3...\n");
	buildPotential3 (
		soluteCoors,		//MoleculeCoordinates *soluteCoors,
		shortPotential,	//SiteSitePotential *siteSitePotential,
		m_beta,
		m_betaUshort			//Solution3DRISMR *potential3D // output
	);

#else
printf("buildPotential2...\n");
	buildPotential2 (
		soluteCoors,		//MoleculeCoordinates *soluteCoors,
		shortPotential,	//SiteSitePotential *siteSitePotential,
		m_betaUshort			//Solution3DRISMR *potential3D // output
	);

#endif //AVERAGE EXP POT

#endif //use buildPotential2

#if USE_buildPotential4
printf("buildPotential4...\n");
	buildPotential4 (
		soluteCoors,		//MoleculeCoordinates *soluteCoors,
		shortPotential,	//SiteSitePotential *siteSitePotential,
		m_beta,
		m_betaUshort			//Solution3DRISMR *potential3D // output
	);



#endif

#if DEBUG_POTENTIAL
int i;
for(i=0;i<m_betaUshort->getNumberOfSites();i++)
{
	char fname[256];
	sprintf(fname,"pot%d.3d",i);
	writeDoubleArrayToFile(fname,m_betaUshort->getGamma()[i], m_betaUshort->getSizeOfOneGamma());

}

#endif


printf("...done\n");

	mulScalarSolution3DRISMR(m_betaUshort, -m_beta );
}

//void GridDependent3DRISM3::initTheta(
//			MoleculeCoordinates *soluteCoors,
//			SiteMultiplicities *siteMultiplicities, 
//			SiteSitePotential *longPotentialK
//		)	
void GridDependent3DRISM3::initTheta(
			MoleculeCoordinates *soluteCoors,
			MoleculeCharges *soluteCharges,
			MoleculeCharges *solventCharges,
			SiteMultiplicities *siteMultiplicities, 
			TabFunction ***phiIndex,
			Real **analyticChiMultipliers
//			SiteSitePotential *longPotentialK
		)
{
	SolutionFactory3DRISMR thetaFactory(m_numSolventSites);
	m_theta = (Solution3DRISMR *)thetaFactory.createSolution(m_grid);
//	m_betaUlong = (Solution3DRISMK *)thetaFactory.createSolution(m_grid);

	GridIndependent3DRISM3 *gridIndependent = (GridIndependent3DRISM3*)getGridIndependent();
	TabFunction ***phiLJIndex = gridIndependent->getPhiLJIndex();
	SigmaEpsilonTable *sigmaEpsilonTable = gridIndependent->getSigmaEpsilonTable();

#if NO_THETA
	m_theta->setZero();
//	m_betaUlong->setZero();
#else

/*	calculateTheta2(	m_beta,			//Real beta,
			soluteCoors,		//MoleculeCoordinates *soluteCoors,
			siteMultiplicities,	//SiteMultiplicities *siteMultiplicities,
			longPotentialK,		//SiteSitePotential *longPotentialK,
			m_chiIndex,		//Solution3DRISMK ***chiIndex,
			m_chiMultipliers,	//Real **chiMultipliers
			m_theta	,		//Solution3DRISMK *theta // out
			m_betaUlong
		   );*/
#if USE_buildAnalyticalTheta
	buildAnalyticalTheta2(
			soluteCoors,	//MoleculeCoordinates *soluteCoors,
			soluteCharges,	//MoleculeCharges *soluteCharges,
			solventCharges,	//MoleculeCharges *solventCharges,
			siteMultiplicities,	//SiteMultiplicities *siteMultiplicities,
			phiIndex,		//TabFunction  ***phiIndex,
			phiLJIndex,		//TabFunction  ***phiLJIndex,
			sigmaEpsilonTable,	//SigmaEpsilonTable *
			analyticChiMultipliers,	//Real **chiMultipliers,
			m_theta			//Solution3DRISMR *theta // out
		   );

#endif

#endif

}

void GridDependent3DRISM3::initClosure(ClosureFactory3DRISM *closureFactory)
{
	m_closure =closureFactory->createClosure3DRISM(
					m_betaUshort //Solution3DRISMR *betaUshort
					);
}

