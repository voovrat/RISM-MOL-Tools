#ifndef NestedPlainSubFactory_h
#define NestedPlainSubFactory_h

#include "NestedSolverSubFactory.h"

class BlackBoxSolver;
#include "Operations.h"
class MGFactoryCollection;


class NestedPlainSubFactory : public NestedSolverSubFactory
{
protected:

	Operations *m_operations;
	MGFactoryCollection *m_factories;
	

public:

	NestedPlainSubFactory(	Operations *operations,
					MGFactoryCollection *factories )
	{
		m_operations = operations;
		m_factories = factories;
	}
	


	virtual BlackBoxSolver * createBlackBoxSolver(	
					ConditionFactory *conditionFactory, 
					Grid *grid,	
					Integer depth			
					);
		
};

#endif
