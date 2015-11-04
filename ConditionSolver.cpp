#include "ConditionSolver.h"

#include "performIterationStepsUntil.h"

void ConditionSolver::solve(	Solution *initialGuess,
				Solution *gridDifference, 
				Solution *result)
{
	performIterationStepsUntil(	m_condition,
				   	m_iterationStep,
			    		initialGuess, 
			    		gridDifference,
			 		result,
					m_solutionFactory);
}

