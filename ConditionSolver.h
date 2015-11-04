#ifndef FixedAccuracySolver_h
#define FixedAccuracySolver_h

#include "Solver.h"
class IterationStep;
class SolutionFactory;
class Condition;
#include "GridDependentData.h"

#include "Condition.h"

class ConditionSolver : public Solver
{
protected:

	Condition *m_condition;
	SolutionFactory *m_solutionFactory;

public:
	
	 ConditionSolver(	Grid *grid,
				Condition *condition,
				SolutionFactory *solutionFactory,
				IterationStep *iterationStep
				//,Real tolerance =0
				)
	: Solver(	grid
			,iterationStep
			,solutionFactory
			//,tolerance
	)
	{
		m_condition = condition;
		m_solutionFactory = solutionFactory;
	}
    	
	virtual void solve(Solution *guess,Solution *gridDifference, Solution *result);
	virtual void solve(Solution *guess,Solution *result)
	{
		Solver::solve(guess,result);
	}
};

class ConditionSolverFactory : public SolverFactory
{
protected:
	ConditionFactory *m_conditionFactory;
	SolutionFactory *m_solutionFactory;
	Real m_tolerance;

public:
	ConditionSolverFactory(	ConditionFactory *conditionFactory,
				SolutionFactory *solutionFactory,
				Real tolerance=0)
	{
		m_conditionFactory = conditionFactory;
		m_solutionFactory = solutionFactory;
		m_tolerance = tolerance;

	}	


	Solver *createSolver(	IterationStep *iterationStep,
				GridDependentData *gridDependent
			)
	{
		Condition *condition = m_conditionFactory->createCondition(gridDependent);

		Solver *solver =new ConditionSolver (
						gridDependent->getGrid(),
						condition,
						m_solutionFactory,
						iterationStep
						//,m_tolerance
					);

		solver->addToDeleteList(condition);
		return solver;
	}

};

#endif
