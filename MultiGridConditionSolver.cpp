#include "MultiGridConditionSolver.h"

#include "MGFactoryCollection.h"
#include "MultiGrid.h"
#include "performIterationStepsUntil.h"
//#include "Statistics.h"


MultiGridConditionSolver::MultiGridConditionSolver(
			MultiGrid *multiGrid,
			Condition *condition,
			SolutionFactory *solutionFactory,
			MultiGridIterationStepFactory *multiGridIterationStepFactory)
: BlackBoxSolver(multiGrid->getGrid(0))
{
	m_condition = condition;
	m_multiGrid = multiGrid;
	m_solutionFactory = solutionFactory;
	m_multiGridIterationStepFactory=multiGridIterationStepFactory;
}

void MultiGridConditionSolver::solve(Solution *initialGuess,Solution *result)
{

	IterationStep *mgIterationStep=
		m_multiGridIterationStepFactory->
			createMultiGridIterationStep(0,m_multiGrid);

	Solution *zero = m_solutionFactory->createSolution(m_initialGuessGrid);
	zero->setZero();

//	Statistics::getInstance()->startIteration();

	 performIterationStepsUntil(m_condition,
				mgIterationStep,
			    	initialGuess, 
			    	zero,	//Solution *gridDifference,
			 	result,
				m_solutionFactory);

//	Statistics::getInstance()->endIteration();


	NULL_DELETE(mgIterationStep);
	NULL_DELETE(zero);
}

BlackBoxSolver *MultiGridConditionSolverFactory::createBlackBoxSolver(Grid *initialGuessGrid)
{

	MultiGrid *mg
		=new MultiGrid(	initialGuessGrid, 	//Grid *grid0,
			m_operations,		//Operations *operations,
			m_factories,		//MGFactoryCollection *factories,
			m_depth,		//Integer depth, 
			m_preSmoothingSteps, 
			m_postSmoothingSteps, 
			m_numberOfMultiGridSubSteps);

	mg->init();

	GridDependentData *gridDependent = 
		m_factories->createGridDependent(initialGuessGrid);

	Condition *condition = m_conditionFactory->createCondition(gridDependent);
	condition->addToDeleteList(gridDependent);


	MultiGridConditionSolver *multiGridConditionSolver = 
		new MultiGridConditionSolver
			(	mg,
				condition,	
				m_factories->m_solutionFactory,
				m_multiGridIterationStepFactory
			);

	multiGridConditionSolver->addToDeleteList(condition);
	multiGridConditionSolver->addToDeleteList(mg);


	return multiGridConditionSolver;
		
}

