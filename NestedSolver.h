#ifndef NestedSolver_h
#define NestedSolver_h

#include "BlackBoxSolver.h"
#include "Operations.h"

class NestedSolverSubFactory;

class MGFactoryCollection;
class ConditionFactory;
class SolutionFactory;
class Grid;
class GridIndependentData;


class NestedSolver : public BlackBoxSolver
{
protected:
	ConditionFactory *m_fineConditionFactory;
	ConditionFactory *m_coarseConditionFactory;

	GridIndependentData *m_gridIndependent;

	MGFactoryCollection *m_factories;
	Operations *m_operations;

	Grid *m_fineGrid;
	Grid *m_coarseGrid;

  	Integer m_depth;	
	NestedSolverSubFactory *m_subFactory;

public:
	NestedSolver(
			ConditionFactory *fineConditionFactory,
			ConditionFactory *coarseConditionFactory,
			Operations *operations,
			MGFactoryCollection *factories,
	//		GridIndependentData *gridIndependent,
			Grid	*fineGrid,
			Integer depth,
			NestedSolverSubFactory *subFactory
			);


	void solve(Solution *initialGuess,Solution *result);

};

class NestedSolverFactory : public BlackBoxSolverFactory
{
protected:

	Operations *m_operations;
	ConditionFactory *m_fineConditionFactory;
	ConditionFactory *m_coarseConditionFactory;
	MGFactoryCollection *m_factories;
	Integer m_depth;
	NestedSolverSubFactory *m_subFactory;
//	GridIndependentData *m_gridIndependent;
public:
	NestedSolverFactory(
			ConditionFactory *fineConditionFactory,
			ConditionFactory *coarseConditionFactory,
			Operations *operations,
			MGFactoryCollection *factories,
			//GridIndependentData *gridIndependent,
			//Grid	*fineGrid,
			Integer depth,
			NestedSolverSubFactory *subFactory
			)
	{
		m_fineConditionFactory = fineConditionFactory;
		m_coarseConditionFactory = coarseConditionFactory;
		m_operations = operations;
		m_factories = factories;
//		m_gridIndependent = factories->getGridIndependent();
		m_depth = depth;
		m_subFactory = subFactory;
	}


	BlackBoxSolver *createBlackBoxSolver(Grid *initialGuessGrid)
	{
		BlackBoxSolver *solver = new NestedSolver(
					m_fineConditionFactory,		//ConditionFactory *fineConditionFactory,
					m_coarseConditionFactory,	//ConditionFactory *coarseConditionFactory,
					m_operations,			//Operations *operations,
					m_factories,			//MGFactoryCollection *factories,
				//	m_gridIndependent,		//GridIndependentData *gridIndependent,
					initialGuessGrid,		//Grid	*fineGrid,
					m_depth,			//Integer depth
					m_subFactory
					);

		return solver;

	}

};

#endif

