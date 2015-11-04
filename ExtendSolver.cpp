#include "ExtendSolver.h"

#include "BlackBoxSolver.h"
#include "Solution.h"
#include "Grid.h"

void ExtendSolver::init()
{Integer i;
	m_grids = new Grid*[m_numberOfExtentions];
	m_x = new Solution*[m_numberOfExtentions];
	m_y = new Solution*[m_numberOfExtentions];

	m_grids[0]=m_initialGuessGrid->clone();

	for(i=1;i<m_numberOfExtentions;i++)
	{
		m_grids[i] = m_initialGuessGrid->factory();
		(*m_extendGrid)(m_grids[i-1],m_grids[i]);
	}
 
}


ExtendSolver::~ExtendSolver()
{Integer i;

	for(i=0;i<m_numberOfExtentions;i++)
	{
		NULL_DELETE(m_grids[i]); 
	}
	
	delete [] m_grids;
	delete [] m_x;
	delete [] m_y;
}

void ExtendSolver::solve(	Solution *initialGuess, 
		Solution *result)
{Integer i;

	m_x[0] = m_solutionFactory->createSolution(m_grids[0]);
	initialGuess->copy(m_x[0]);
		
	for(i=0;i<m_numberOfExtentions;i++)
	{
		BlackBoxSolver *solver = 
			m_subSolverFactory->createBlackBoxSolver(m_grids[i]);
	
		m_y[i] = m_solutionFactory->createSolution(m_grids[i]);

		solver->solve(m_x[i],m_y[i]);

		NULL_DELETE(m_x[i]);


		if(i<m_numberOfExtentions-1)
		{
			m_x[i+1] = m_solutionFactory->createSolution(m_grids[i+1]);
			(*m_extendSolution)(m_y[i],m_x[i+1]);
			NULL_DELETE(m_y[i]);
		}

		NULL_DELETE(solver);
	}

	m_y[m_numberOfExtentions-1]->copy(result);
	NULL_DELETE(m_y[m_numberOfExtentions-1]);
}




