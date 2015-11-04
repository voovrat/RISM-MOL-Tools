#ifndef GridDependent3DRISM3_h
#define GridDependent3DRISM3_h

#include "GridDependentInterface3DRISM.h"

#include <stdio.h>
#include "Settings.h"
#include "stacktrace.h"

#include "Exception.h"

class Grid3DRISM;
class Solution3DRISMR;
class Solution3DRISMK;

class MoleculeCoordinates;
class MoleculeCharges;
class SiteSitePotential;
class TabFunction;

class Closure3DRISM;
class ClosureFactory3DRISM;

class SiteMultiplicities;
class OmegaData;
class SiteDensities;

class GridDependent3DRISM3 : public GridDependentInterface3DRISM
{
protected:

	Integer m_numSolventSites;
	Integer m_numChi;
	Real m_beta;

	Solution3DRISMR *m_betaUshort;
	Solution3DRISMR *m_theta;
//	Solution3DRISMK *m_betaUlong;//-betaUlong(K)
	Solution3DRISMK **m_chi3D;
	Solution3DRISMK ***m_chiIndex;
	OmegaData *m_omegaData;

	Closure3DRISM *m_closure;
	Real **m_chiMultipliers;

	void initChi(	TabFunction **solventRDFs,
			SiteDensities *,
			OmegaData *omegaData
			);

	void initShortPotential(MoleculeCoordinates *soluteCoors,
				SiteSitePotential *shortPotential);

	void initTheta(	MoleculeCoordinates *soluteCoors,
			MoleculeCharges *soluteCharges,
			MoleculeCharges *solventCharges,
			SiteMultiplicities *siteMultiplicities, 
			TabFunction ***phiIndex,
			Real **analyticChiMultipliers
//			SiteSitePotential *longPotentialK
		);

	void initClosure(ClosureFactory3DRISM *closureFactory);
	

public:

	GridDependent3DRISM3(	GridIndependentData *gridIndependent,
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
				
			);

	virtual ~GridDependent3DRISM3();


#if DEBUG_LEAKS
	virtual void retain()
	{
		FILE *f=fopen("leaks.txt","r+");		
		fseek(f,0,SEEK_END);
		fprintf(f,"RETAIN : this %p\n",this);
		prInteger_stacktrace(f);
		fclose(f);

		Object::retain();

	}
	virtual void release()
	{
		FILE *f=fopen("leaks.txt","r+");
		fseek(f,0,SEEK_END);		
		fprintf(f,"RELEASE : this %p\n",this);
		prInteger_stacktrace(f);
		fclose(f);

		Object::release();
	}

	
#endif

	Integer getNumChi()
	{
		return m_numChi;
	}

	Solution3DRISMR *getBetaUshort()
	{
		return m_betaUshort;
	}

	Solution3DRISMR *getThetaR()
	{
		return m_theta;
	}

	Solution3DRISMK *getTheta()
	{
		throw new Exception(this,"GridDependent3DRISM3::getTheta : one should not get Theta in K space. Use getThetaR instead");

		return NULL;
	}

	Solution3DRISMK **getChi3D()
	{
		return m_chi3D;
	}

	Solution3DRISMK ***getChiIndex()
	{
		return m_chiIndex;
	}

	Closure3DRISM *getClosure()
	{
		return m_closure;
	}

//	Solution3DRISMK *getBetaUlong()
//	{
//		return m_betaUlong;
//	}
	
	Real **getChiMultipliers()
	{
		return m_chiMultipliers;
	}

};


#endif
