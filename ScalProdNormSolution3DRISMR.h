#ifndef scalProdNormSolution3DRISMR_h
#define scalProdNormSolution3DRISMR_h

#include "Norm.h"
#include "GridDependentNormFactory.h"

class ScalProdNormSolution3DRISMR : public Norm
{
public:
	virtual Real calculateNorm(Object *x,Object *y);

};

class ScalProdNormSolution3DRISMRFactory : public GridDependentNormFactory
{
public:
	virtual Norm *createNorm(GridDependentData *)
	{
		return new ScalProdNormSolution3DRISMR();	
	}
};

#endif
