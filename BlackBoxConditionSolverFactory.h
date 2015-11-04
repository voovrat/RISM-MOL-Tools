#ifndef BlackBoxConditionSolver_h
#define BlackBoxConditionSolver_h

#include "Object.h"
#include "BlackBoxSolver.h"

class Grid;
class OperatorFactory;
class IterationStepFactory;
class ConditionFactory;
class SolutionFactory;
class GridIndependentData;

class BlackBoxConditionSolverFactory : public BlackBoxSolverFactory
{
protected:
	GridIndependentData *m_gridIndependent;
	OperatorFactory *m_operatorFactory;
	IterationStepFactory *m_iterationStepFactory;
	ConditionFactory *m_conditionFactory;
	SolutionFactory *m_solutionFactory;
	

public:
	BlackBoxConditionSolverFactory(	GridIndependentData *gridIndependent,
					OperatorFactory *operatorFactory,
					IterationStepFactory *iterationStepFactory,
					ConditionFactory *conditionFactory,
					SolutionFactory *solutionFactory
					);



	virtual BlackBoxSolver *createBlackBoxSolver(Grid *grid);

};


#endif
