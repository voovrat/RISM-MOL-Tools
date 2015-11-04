#ifndef HNCFreeEnergy3DRISM_h
#define HNCFreeEnergy3DRISM_h

#include "FreeEnergy.h"

class SolutionFactory3DRISMR;
class Solution3DRISMK;
class Grid3DRISM;
class Closure3DRISM;
class Solution3DRISMR;

class HNCFreeEnergy3DRISM : public FreeEnergy
{
protected:
	Closure3DRISM *m_closure;
	SolutionFactory3DRISMR *m_solutionFactory;
//	Solution3DRISMR *m_longPot;
	Grid3DRISM *m_grid;
	Real *m_densities;
	Integer *m_multiplicities;
	Real m_kBT;
	
public:
	HNCFreeEnergy3DRISM(	Closure3DRISM *closure,
			//	Solution3DRISMK *betaUlongPotK,//-beta*longPot(K)
				SolutionFactory3DRISMR *solutionFactory,
				Real *densities, //[Bohr^-3]
				Integer *multiplicities,
				Real kBT	//[Hartree]
			);

	virtual ~HNCFreeEnergy3DRISM();

	virtual Real calculateFreeEnergy(Solution *gamma);
};

class HNCFreeEnergyFactory3DRISM : public FreeEnergyFactory
{
protected:
	SolutionFactory3DRISMR *m_solutionFactory;
//	int m_noBetaU;
public:
	HNCFreeEnergyFactory3DRISM(SolutionFactory3DRISMR *solutionFactory/*,int noBetaU=1*/)
	{
		m_solutionFactory = solutionFactory;
		//m_noBetaU=noBetaU;
	}

	virtual FreeEnergy *createFreeEnergy(GridDependentData *gridDependent);

};


#endif
