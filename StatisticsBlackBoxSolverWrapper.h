#ifndef StatisticsBlackBoxSolverWrapper_h
#define StatisticsBlackBoxSolverWrapper_h

#include "Settings.h"
#include "Object.h"
#include "BlackBoxSolver.h"

class StatisticsBlackBoxSolverWrapper : public BlackBoxSolver
{
protected:
	BlackBoxSolver *m_blackBoxSolver;
public:
	StatisticsBlackBoxSolverWrapper( BlackBoxSolver *blackBoxSolver)
	: BlackBoxSolver(NULL)
	{
		m_blackBoxSolver = blackBoxSolver;
	}

	virtual void solve(Solution *initialGuess,Solution *result);

	virtual Grid *getResultGrid()
	{
		return m_blackBoxSolver->getResultGrid();
	}

	

};

class StatisticsBlackBoxSolverWrapperFactory : public BlackBoxSolverFactory
{
protected:
	BlackBoxSolverFactory *m_blackBoxSolverFactory;
public:
	StatisticsBlackBoxSolverWrapperFactory(BlackBoxSolverFactory *blackBoxSolverFactory)
	{
		m_blackBoxSolverFactory = blackBoxSolverFactory;
	}

	virtual BlackBoxSolver *createBlackBoxSolver(Grid *initialGuessGrid)
	{
		BlackBoxSolver *blackBoxSolver = m_blackBoxSolverFactory->createBlackBoxSolver(initialGuessGrid);

		StatisticsBlackBoxSolverWrapper *r =new StatisticsBlackBoxSolverWrapper( blackBoxSolver );
		r->addToDeleteList(blackBoxSolver);
		return r;
	}
};


#endif
