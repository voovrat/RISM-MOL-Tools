#ifndef NestedMultiGridSubFactory_h
#define NestedMultiGridSubFactory_h

#include "NestedSolverSubFactory.h"

class BlackBoxSolver;
#include "Operations.h"
class MGFactoryCollection;


class NestedMultiGridSubFactory : public NestedSolverSubFactory
{
protected:

	Operations *m_operations;
	MGFactoryCollection *m_factories;
	Integer m_preSmoothingSteps;
	Integer m_subSteps;
	Integer m_postSmoothingSteps;
	

public:

	NestedMultiGridSubFactory(	Operations *operations,
					MGFactoryCollection *factories,
					Integer preSmoothingSteps,
					Integer postSmoothingSteps,
					Integer	subSteps )
	{
		m_operations = operations;
		m_factories = factories;
		m_preSmoothingSteps = preSmoothingSteps;
		m_postSmoothingSteps = postSmoothingSteps;
		m_subSteps = subSteps;
	}
	


	virtual BlackBoxSolver * createBlackBoxSolver(	
					ConditionFactory *conditionFactory, 
					Grid *grid,	
					Integer depth			
					);
		
};

#endif
