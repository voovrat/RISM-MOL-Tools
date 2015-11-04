#ifndef GridDependentNormFactory_h
#define GridDependentNormFactory_h

#include "Norm.h"
class GridDependentData;

class GridDependentNormFactory : public Object
{
public:
	virtual Norm *createNorm(GridDependentData *)=0;

};

#endif
