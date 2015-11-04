#ifndef MultiGridConditionSolver_h
#define MultiGridConditionSolver_h

#include "BlackBoxSolver.h"
#include "Operations.h"

class MGFactoryCollection;
class MultiGrid;
class Condition;
class MultiGridIterationStepFactory;
class SolutionFactory;

class MultiGridConditionSolver : public BlackBoxSolver
{
protected:
	Condition *m_condition;
	MultiGrid *m_multiGrid;
	SolutionFactory *m_solutionFactory;
	MultiGridIterationStepFactory *m_multiGridIterationStepFactory;

public:
	MultiGridConditionSolver(
			MultiGrid *multiGrid,
			Condition *condition,
			SolutionFactory *solutionFactory,
			MultiGridIterationStepFactory *multiGridIterationStepFactory);


	void solve(Solution *initialGuess,Solution *result);

};

class MultiGridConditionSolverFactory : public BlackBoxSolverFactory
{
protected:

	Operations *m_operations;
	ConditionFactory *m_conditionFactory;
	MGFactoryCollection *m_factories;
	Integer m_depth;
	MultiGridIterationStepFactory *m_multiGridIterationStepFactory;
	Integer m_preSmoothingSteps;
	Integer m_postSmoothingSteps;
	Integer m_numberOfMultiGridSubSteps;

public:

	MultiGridConditionSolverFactory
		(	ConditionFactory *conditionFactory, 
		 	Operations *operations,
			MGFactoryCollection *factories,
			Integer depth, 
			MultiGridIterationStepFactory *multiGridIterationStepFactory,
			Integer preSmoothingSteps=1, 
			Integer postSmoothingSteps=0, 
			Integer numberOfMultiGridSubSteps=1
		)
	{
		m_operations = operations;
		m_factories = factories;
		m_depth = depth;
		m_preSmoothingSteps = preSmoothingSteps;
		m_postSmoothingSteps = postSmoothingSteps;
		m_numberOfMultiGridSubSteps = numberOfMultiGridSubSteps;
		m_multiGridIterationStepFactory = multiGridIterationStepFactory;
		m_conditionFactory = conditionFactory;
	}


	BlackBoxSolver *createBlackBoxSolver(Grid *initialGuessGrid);

};


#endif

