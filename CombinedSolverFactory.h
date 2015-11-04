#ifndef CombinedSolverFactory_h
#define CombinedSolverFactory_h

// if grid==grid0 -> firstSolverFactory 
// if grid!=grid0 -> secondSolverFactory

#include "BlackBoxSolver.h"
#include "Grid.h"

class CombinedSolverFactory : public BlackBoxSolverFactory
{
protected:
	Grid *m_grid;
	BlackBoxSolverFactory *m_firstSolverFactory;
	BlackBoxSolverFactory *m_secondSolverFactory;
	

public: 
	CombinedSolverFactory(	BlackBoxSolverFactory *firstSolverFactory,
				BlackBoxSolverFactory *secondSolverFactory )
	{
		m_grid=NULL;
		m_firstSolverFactory = firstSolverFactory;
		m_secondSolverFactory = secondSolverFactory;

	}

	virtual ~CombinedSolverFactory()
	{
		NULL_DELETE(m_grid);
	}

	virtual BlackBoxSolver *createBlackBoxSolver( Grid *grid)
	{
		if( !m_grid )
		{
			m_grid = grid->clone();
		}

		BlackBoxSolver *solver;

		if( m_grid->isEqual(grid))
			solver = m_firstSolverFactory->createBlackBoxSolver( grid );
		else
			solver = m_secondSolverFactory->createBlackBoxSolver( grid );


		return solver;
	}

};

#endif
