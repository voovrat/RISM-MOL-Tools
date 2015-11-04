#ifndef MGFactoryCollection_h
#define MGFactoryCollection_h

//class GridDependentFactory;
class OperatorFactory;
class IterationStepFactory;
class SolverFactory;
class SolutionFactory;


class MGFactoryCollection
{
public:

	GridIndependentData *m_gridIndependent;
	OperatorFactory * m_operatorFactory;

	IterativeStepFactory *m_fineGridStepFactory;
	IterativeStepFactory *m_coarseGridStepFactory;
	SovlerFactory *m_coarseGridSolverFactory;
		
	SolutionFactory *m_solutionFactory;

protected:

	IterationStep *createIterationStep(	GridDependentData *gridDependent,
						IterationStepFactory *iteratonStepFactory)
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
	IterativeStepFactory *fineGridStepFactory,
	IterativeStepFactory *coarseGridStepFactory,
	SovlerFactory *coarseGridSolverFactory,
	SolutionFactory *m_solutionFactory
	)
	{

	m_gridIndependent=gridIndependent;
	m_operatorFactory=operatorFactory;

	m_fineGridStepFactory=fineGridStepFactory;
	m_coarseGridStepFactory=coarseGridStepFactory;
	m_coarseGridSolverFactory=coarseGridSolverFactory;
		
	m_solutionFactory=solutionFactory;

	}

	GridIndependetData *getGridIndependent()
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

		Solver *solver = m_coarseGridSolverFactory->createSolver(iterationStep);

		solver->addToDeleteList(iterationStep);

		return solver;
	}

	Solution *createSolution(Grid *g)
	{
		return m_solutionFactory->createSolution(g);
	}
};


#endif
