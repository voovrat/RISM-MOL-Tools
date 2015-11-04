#include "NestedMultiGridSubFactory.h"

#include "BlackBoxSolver.h"
#include "MultiGridConditionSolver.h"
#include "MultiGrid.h"
#include "Grid.h"

BlackBoxSolver * NestedMultiGridSubFactory::createBlackBoxSolver(	
					ConditionFactory *conditionFactory,
					Grid *grid, 
					Integer depth			
					)
{

MultiGridIterationStepFactory *stepFactory = MultiGridIterationStepFactory::getInstance();


MultiGridConditionSolverFactory *solverFactory = new MultiGridConditionSolverFactory
		(	conditionFactory,		//ConditionFactory *conditionFactory, 
			m_operations,			//Operations *operations,
			m_factories,			//MGFactoryCollection *factories,
			depth,				//Integer depth, 
			stepFactory,			//MultiGridIterationStepFactory *multiGridIterationStepFactory,
			m_preSmoothingSteps,		//Integer preSmoothingSteps=1, 
			m_postSmoothingSteps,		//Integer postSmoothingSteps=0, 
			m_subSteps		//Integer numberOfMultiGridSubSteps=1
		);

BlackBoxSolver *solver = solverFactory->createBlackBoxSolver(grid);


NULL_DELETE(solverFactory);

return solver;
}

