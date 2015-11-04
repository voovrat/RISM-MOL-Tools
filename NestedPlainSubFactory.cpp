#include "NestedPlainSubFactory.h"

#include "BlackBoxSolver.h"
#include "Grid.h"
#include "BlackBoxConditionSolverFactory.h"
#include "MGFactoryCollection.h"


BlackBoxSolver * NestedPlainSubFactory::createBlackBoxSolver(	
					ConditionFactory *conditionFactory,
					Grid *grid, 
					Integer depth			
					)
{

	BlackBoxSolverFactory *solverFactory= new BlackBoxConditionSolverFactory(
			m_factories->m_gridIndependent, //	GridIndependentData *gridIndependent,
			m_factories->m_operatorFactory,//	OpertorFactory *operatorFactory,
			m_factories->m_coarseGridStepFactory,//IterationStepFactory *iterationStepFactory,
			conditionFactory,//ConditionFactory *conditionFactory,
			m_factories->m_solutionFactory //		SolutionFactory *solutionFactory
	);


BlackBoxSolver *solver = solverFactory->createBlackBoxSolver(grid);


NULL_DELETE(solverFactory);

return solver;
}

