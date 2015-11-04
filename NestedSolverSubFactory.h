#ifndef NestedSolverSubFactory_h
#define NestedSolverSubFactory_h

#include "Object.h"

class BlackBoxSolver;
class ConditionFactory;
class Grid;

class NestedSolverSubFactory : public Object
{
public:

	virtual BlackBoxSolver * createBlackBoxSolver(	
					ConditionFactory *conditionFactory, 
					Grid *grid,
					Integer depth			
					) 
					=0;
		
};

#endif
