#ifndef GridDependentInterface3DRISM_h
#define GridDependentInterface3DRISM_h

#include "GridDependentData.h"

class Solution3DRISMR;
class Solution3DRISMK;
class Closure3DRISM;

#include "Exception.h"

class GridDependentInterface3DRISM : public GridDependentData
{
public:

	GridDependentInterface3DRISM(Grid *grid,GridIndependentData *gridIndependent)
	: GridDependentData(grid,gridIndependent) 
	{}

	virtual Integer getNumChi()
	{
		throw new Exception(this,"GridDependentInterface3DRISM::getNumChi: this function is a stub.");
		return 0;	
	}

	virtual Solution3DRISMR *getBetaUshort()
	{
		throw new Exception(this,"GridDependentInterface3DRISM::getBetaUshort : this function is a stub. ");
		return NULL;
	}
	virtual Solution3DRISMK *getTheta()
	{
		throw new Exception(this,"GridDependentInterface3DRISM::getTheta : this function is a stub. ");
		return NULL;
	}

	virtual Solution3DRISMR *getThetaR()
	{
		throw new Exception(this,"GridDependentInterface3DRISM::getThetaR : this function is a stub. Probably you should use another derivative class, or getTheta() instead");
		return NULL;
	}
	virtual Solution3DRISMK **getChi3D()
	{
		throw new Exception(this,"GridDependentInterface3DRISM::getChi3D : this function is a stub. ");
		return NULL;
	}

	virtual Solution3DRISMK ***getChiIndex()
	{
		throw new Exception(this,"GridDependentInterface3DRISM::getChiIndex : this function is a stub. ");
		return NULL;
	}
	
	virtual Closure3DRISM *getClosure()
	{
		throw new Exception(this,"GridDependentInterface3DRISM::getClosure : this function is a stub. ");
		return NULL;
	}
	virtual Solution3DRISMK *getBetaUlong()//-beta U long(K)
	{
		throw new Exception(this,"GridDependentInterface3DRISM::getBetaUlong : this function is a stub. ");
		return NULL;
	}
	virtual Real **getChiMultipliers()
	{
		throw new Exception(this,"GridDependentInterface3DRISM::getChiMultipliers : this function is a stub. ");
		return NULL;
	}

};


#endif
