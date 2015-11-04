#ifndef ExtendSolver_h
#define ExtendSolver_h


#include "BinaryOperation.h"

#include "BlackBoxSolver.h"
class Grid;
class Solution;
class SolutionFactory;

class ExtendSolver : public BlackBoxSolver
{
protected:

	BlackBoxSolverFactory *m_subSolverFactory;
	Integer m_numberOfExtentions;
	SolutionFactory *m_solutionFactory;
//	void (*m_extendSolution)(Solution *,Solution *);
//	void (*m_extendGrid)(Grid *,Grid *);

	BinaryOperation<Solution *> *m_extendSolution;
	BinaryOperation<Grid *> *m_extendGrid;


	Grid **m_grids;
	Solution **m_x;
	Solution **m_y;

	void init();
	
	

public:

	ExtendSolver(	Grid *initialGuessGrid,
			BlackBoxSolverFactory *subSolverFactory,
			Integer numberOfExtentions,
			SolutionFactory *solutionFactory,
			//void (*extendSolution)(Solution *,Solution *),
			//void (*extendGrid)(Grid *,Grid *)
			BinaryOperation<Solution *> *extendSolution,
			BinaryOperation<Grid *> *extendGrid
			)
	: BlackBoxSolver(initialGuessGrid)
	{
		m_subSolverFactory = subSolverFactory;
		m_solutionFactory = solutionFactory;
		m_numberOfExtentions = numberOfExtentions+1;
		m_extendSolution = extendSolution;
		m_extendGrid = extendGrid;

		init();
	}

	virtual ~ExtendSolver();

	void solve(	Solution *initialGuess, 
			Solution *result);

	virtual Grid *getResultGrid()
	{
		return m_grids[m_numberOfExtentions-1];
	}

};

class ExtendSolverFactory : public BlackBoxSolverFactory
{
protected:


//	void (*m_extendSolution)(Solution *,Solution *);
//	void (*m_extendGrid)(Grid *,Grid *);

	BinaryOperation<Solution *> *m_extendSolution;
	BinaryOperation<Grid *> *m_extendGrid;

	SolutionFactory *m_solutionFactory;
	BlackBoxSolverFactory *m_subSolverFactory;
	Integer m_numberOfExtentions;

public:
	ExtendSolverFactory(	
		Integer numberOfExtentions,
		SolutionFactory *solutionFactory,
		BlackBoxSolverFactory *subSolverFactory,
		BinaryOperation<Solution *> *extendSolution,
		BinaryOperation<Grid *> *extendGrid
	)
	{
		m_solutionFactory = solutionFactory;
		m_subSolverFactory = subSolverFactory;
		m_extendSolution = extendSolution;
		m_extendGrid = extendGrid;
		m_numberOfExtentions = numberOfExtentions;
	}

	virtual BlackBoxSolver *createBlackBoxSolver(Grid *initialGuessGrid)
	{
	return new ExtendSolver(
		initialGuessGrid, 	//Grid *initialGuessGrid,
		m_subSolverFactory, 	//BlackBoxSolverFactory *subSolverFactory,
		m_numberOfExtentions, 	//Integer numberOfExtentions,
		m_solutionFactory,	//SolutionFactory *solutionFactory,
		m_extendSolution,//void (*extendSolution)(Solution *,Solution *),
		m_extendGrid	//void (*extendGrid)(Grid *,Grid *),
		);

	}
};

#endif
