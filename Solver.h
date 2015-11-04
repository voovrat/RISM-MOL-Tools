#ifndef Solver_h
#define Solver_h

class Solution;
class SolutionFactory;
class IterationStep;
class GridDependentData;

#include "BlackBoxSolver.h"

// Solver is the interface for different one-grid solvers.
// Concret solver should be derived from the current class.
// Solver interface have only one function: solve.
// it takes initial guess, Operation and gridDifference.
// It performs iteration steps and put the solution to the last variable (result).
// function does not allocate result - it should be allocated before the function call.

// Concrete implementations of CoarseGridSolver should by themselves determine appropriate number of CoarseGridSteps.
// Different schemes (Dumped Picard Scheme, DIIS, Newton-Raphson) can be derived and implemented. 


class Solver : public BlackBoxSolver
{
 protected:
	IterationStep * m_iterationStep;
	SolutionFactory *m_solutionFactory;

 public:

	Solver( Grid *initialGrid,
		IterationStep *iterationStep
		,SolutionFactory *solutionFactory
	)
	: BlackBoxSolver(initialGrid)
	{
		m_iterationStep = iterationStep;
		m_solutionFactory = solutionFactory;
	}

	virtual ~Solver() {}

	virtual void solve(Solution *guess,Solution *gridDifference, Solution *result)=0;
	virtual void solve(Solution *guess,Solution *result);

};

class SolverFactory : public Object
{
public:

	virtual Solver *createSolver(IterationStep *,GridDependentData *)=0;
};


#endif
