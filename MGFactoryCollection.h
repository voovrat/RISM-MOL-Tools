#ifndef MGFactoryCollection_h
#define MGFactoryCollection_h


#include "Operator.h"
#include "IterationStep.h"
#include "Solver.h"
#include "Solution.h"

#include "GridIndependentData.h"
class GridDependetData;


class MGFactoryCollection : public Object
{
public:

	GridIndependentData *m_gridIndependent;
	OperatorFactory * m_operatorFactory;

	IterationStepFactory *m_fineGridStepFactory;
	IterationStepFactory *m_coarseGridStepFactory;
	SolverFactory *m_coarseGridSolverFactory;
		
	SolutionFactory *m_solutionFactory;

public:

	IterationStep *createIterationStep(	GridDependentData *gridDependent,
						IterationStepFactory *iterationStepFactory)
	{
		Operator *op = createOperator(gridDependent);
		IterationStep *iterationStep = iterationStepFactory->createIterationStep(op);
		iterationStep->addToDeleteList(op);

		return iterationStep;
	}


public:

	MGFactoryCollection() {}


	void init(
	GridIndependentData *gridIndependent,
	OperatorFactory * operatorFactory,
	IterationStepFactory *fineGridStepFactory,
	IterationStepFactory *coarseGridStepFactory,
	SolverFactory *coarseGridSolverFactory,
	SolutionFactory *solutionFactory
	)
	{

	m_gridIndependent=gridIndependent;
	m_operatorFactory=operatorFactory;

	m_fineGridStepFactory=fineGridStepFactory;
	m_coarseGridStepFactory=coarseGridStepFactory;
	m_coarseGridSolverFactory=coarseGridSolverFactory;
		
	m_solutionFactory=solutionFactory;

	}

	GridIndependentData *getGridIndependent()
	{
		return m_gridIndependent;
	}

	GridDependentData *createGridDependent(Grid *g)
	{
		return m_gridIndependent->createGridDependent(g);
	}


public:

	Operator *createOperator(GridDependentData *gridDependent)
	{
		return m_operatorFactory->createOperator(m_gridIndependent,gridDependent);
	}

	IterationStep *createFineGridIterationStep(GridDependentData *gridDependent)
	{
		return createIterationStep(gridDependent,m_fineGridStepFactory);
	}
	
	Solver *createCoarseGridSolver(GridDependentData *gridDependent)
	{
		IterationStep *iterationStep = 
			createIterationStep(gridDependent,m_coarseGridStepFactory);

		Solver *solver = m_coarseGridSolverFactory->createSolver(iterationStep,gridDependent);

		solver->addToDeleteList(iterationStep);

		return solver;
	}

	Solution *createSolution(Grid *g)
	{
		return m_solutionFactory->createSolution(g);
	}
};


#endif
