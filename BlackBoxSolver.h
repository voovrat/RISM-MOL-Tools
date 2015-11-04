#ifndef BlackBoxSolver_h
#define BlackBoxSolver_h

#include "Object.h"

class Grid;
class Solution;

class BlackBoxSolver : public Object
{
protected:
	Grid *m_initialGuessGrid;

public:

	BlackBoxSolver(Grid *initialGuessGrid) 
	{
		m_initialGuessGrid = initialGuessGrid;	
	}

	virtual void solve(Solution *initialGuess,Solution *result) =0;

	Grid *getInitialGuessGrid()
	{
		return m_initialGuessGrid;
	}

	virtual Grid *getResultGrid()
	{
		return m_initialGuessGrid;
	}

};

class BlackBoxSolverFactory : public Object
{
public:
	virtual BlackBoxSolver *createBlackBoxSolver(Grid *initialGuessGrid)=0;

};


#endif
