#include "BlackBoxConditionSolverFactory.h"

#include "GridIndependentData.h"
#include "GridDependentData.h"
#include "Condition.h"
#include "Operator.h"
#include "Solution.h"
#include "IterationStep.h"
#include "ConditionSolver.h"


BlackBoxConditionSolverFactory::BlackBoxConditionSolverFactory(	
					GridIndependentData *gridIndependent,
					OperatorFactory *operatorFactory,
					IterationStepFactory *iterationStepFactory,
					ConditionFactory *conditionFactory,
					SolutionFactory *solutionFactory
					)
{
	m_gridIndependent = gridIndependent;
	m_operatorFactory = operatorFactory;
	m_iterationStepFactory = iterationStepFactory;
	m_conditionFactory = conditionFactory;
	m_solutionFactory = solutionFactory;
}


BlackBoxSolver *BlackBoxConditionSolverFactory::createBlackBoxSolver(Grid *grid)
{
	GridDependentData *gridDependent = m_gridIndependent->createGridDependent(grid);
	Condition *condition = m_conditionFactory->createCondition(gridDependent);
	Operator *op = m_operatorFactory->createOperator(
				m_gridIndependent,//GridIndependentData *,
				gridDependent//GridDependentData *
		);

	IterationStep *iterationStep = m_iterationStepFactory->createIterationStep(op);

	ConditionSolver *solver = new ConditionSolver(	
				gridDependent->getGrid(),	//Grid *grid,
				condition,//Condition *condition,
				m_solutionFactory,//SolutionFactory *solutionFactory,
				iterationStep	//IterationStep *iterationStep
				//,Real tolerance =0
				);

	solver->addToDeleteList(gridDependent);
	solver->addToDeleteList(op);
	solver->addToDeleteList(iterationStep);

	return solver;
}



