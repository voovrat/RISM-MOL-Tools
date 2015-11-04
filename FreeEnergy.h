#ifndef FreeEnergy_h
#define FreeEnergy_h

#include "Object.h"

class Solution;
class GridDependentData;

class FreeEnergy : public Object
{
public:

	virtual Real calculateFreeEnergy(Solution *gamma) =0;
};

class FreeEnergyFactory : public Object
{
public:
	virtual FreeEnergy *createFreeEnergy(GridDependentData *)=0;
};

#endif
