#ifndef L2Norm3DRISM_h
#define L2Norm3DRISM_h

#include "Norm.h"
#include "Exception.h"
#include "GridDependentNormFactory.h"

class SolutionFactory3DRISMR;
class Closure3DRISM;

class L2Norm3DRISM : public Norm
{
protected:
	Closure3DRISM *m_closure;
	SolutionFactory3DRISMR *m_solutionFactory;
public:
	L2Norm3DRISM(	Closure3DRISM *closure,
			SolutionFactory3DRISMR *solutionFactory
			)
	{
		m_closure = closure;
		m_solutionFactory = solutionFactory;
	}

	virtual Real calculateNorm(Object *x,Object *y);
	
};

class L2Norm3DRISMFactory : public GridDependentNormFactory
{
protected:
	SolutionFactory3DRISMR *m_solutionFactory;
public:
	L2Norm3DRISMFactory(SolutionFactory3DRISMR *solutionFactory)
	{
		m_solutionFactory = solutionFactory;
	}

	virtual Norm *createNorm(GridDependentData *gridDependent);

};

#endif
