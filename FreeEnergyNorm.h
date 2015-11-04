#ifndef FreeEnergyNorm_h
#define FreeEnergyNorm_h


#include "Norm.h"
#include "FreeEnergy.h"
#include "GridDependentNormFactory.h"
class Solution;

#include <math.h>

class FreeEnergyNorm : public Norm
{
protected:
	FreeEnergy *m_freeEnergy;

public:
	FreeEnergyNorm(	FreeEnergy *freeEnergy )
	{
		m_freeEnergy = freeEnergy;
	}

	virtual Real calculateNorm(Object *x,Object *y)
	{
		Real freeEnergy1 = m_freeEnergy->calculateFreeEnergy((Solution *)x);
		Real freeEnergy2 = m_freeEnergy->calculateFreeEnergy((Solution *)y);
		
		return fabs(freeEnergy2-freeEnergy1);
	}
};

class FreeEnergyNormFactory : public GridDependentNormFactory
{
protected:
	FreeEnergyFactory *m_freeEnergyFactory;

public:
	FreeEnergyNormFactory(FreeEnergyFactory *freeEnergyFactory)
	{
		m_freeEnergyFactory = freeEnergyFactory;
	}
	
	virtual Norm *createNorm(GridDependentData *gridDependent)
	{
		FreeEnergy *freeEnergy = m_freeEnergyFactory->createFreeEnergy(gridDependent);
		Norm *norm = new FreeEnergyNorm(freeEnergy);
		norm->addToDeleteList(freeEnergy);
		return norm;
	}
};

#endif


