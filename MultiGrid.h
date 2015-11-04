#ifndef multiGrid_h
#define multiGrid_h

#include "Object.h"
#include "Operations.h"
#include "IterationStep.h"

class MGFactoryCollection;
class Grid;
class Solution;
class Solver;
class GridDependentData;

// MultiGrid algorithm.
// usage:
// 1) create MultiGrid class
//        MultiGrid(grid0, operations,  depth, coarseGridSolver)
// 2) initialize solver (create gridDependent and gridIndependent Data)
//          MultiGrid::init function
// 3) Solve the problem        
//      i)   	Create the MultiGridIterationStep of level 0.
//	ii)	Create the solver, which uses these iterations
//	iii)	Run Solver::solve to solve the problem
	
class MultiGrid : public Object
{
 protected:

	friend class MultiGridIterationStep;
   
	// *********** MG Parameters *******************

	Integer m_isInited; // whether or not MultiGrid::init function has been runned
  
	Grid *m_grid0; // the first (finest) grid
	Integer m_depth;   // depth of multi-grid recursion
  	Integer m_preSmoothingSteps, m_postSmoothingSteps; // number of pre and post smoothing iteration steps
	Integer m_numberOfMultiGridSubSteps; // number of multi-grid iteration sub steps in the recursive algorithm (mu parameter)	


	// *********** Grid Dependent data ****************

	Grid **m_grids; // array which contain grids
	GridDependentData **m_gridDependentData;
	Operator **m_operators;
	IterationStep **m_fineGridIterationSteps; // perform one fine-grid iteration		
	Solver *m_coarseGridSolver; // coarse grid solver 

	// ********** Factories & Operations

	Operations *m_operations; // array with function pointers: operation on the Solution and Grid
	MGFactoryCollection *m_factories;


	// ***************** Functions 
 
    	 // function creates and fills the grids array
  	 static Grid **generateGrids(Grid *grid0,Integer depth, void (*restrictGrid)(Grid *,Grid *) );

   	// function NULL_DELETE(s) grid independent and grid dependent data
  	 void unInit();

   	// perform one multi-grid iteration.
  	 void mgm(Integer level, Solution *initialGuess, Solution *gridDifference,Solution *result);


protected: // CALLBACKS

	virtual	void beforePreSmoothing(Integer level,Solution *initialGuess,Solution *fineGridDiff)
	{}

	virtual void afterPreSmoothing(Integer level, Solution *xFine) 
	{}

	virtual void afterGridDifference(Integer level,Solution *coarseGridDifference)
	{}

	virtual void beforeSubIteration(Integer level, Solution *xCoarse)
	{}

	virtual void afterSubIteration(Integer level,Solution *yCoarse)
	{}

	virtual void beforeFineGridCorrection(Integer level,Solution *FineCorr)
	{}

	virtual void afterFineGridCorrection(Integer level,Solution *xFine)
	{}

	virtual void afterPostSmoothing(Integer level,Solution *result)
	{}

public:
   	void calculateGridDifference(
				Integer level,
				Solution *fineSolution,
				Solution *fineGridDifference,
				Solution *result);

 

	Grid *getGrid(Integer level)
	{
		if(!m_isInited || level >= m_depth)
			throw "MultiGrid::getGrid : not inited or level>depth";

		return m_grids[level];
	}

   // construct new MultiGrid object. 
   // needs: zero grid, operations, depth, coarse grid solver. construct grids array
	MultiGrid(	Grid *grid0,
			Operations *operations,
			MGFactoryCollection *factories,
			Integer depth, 
			Integer preSmootingSteps, 
			Integer postSmoothingSteps, 
			Integer numberOfMultiGridSubSteps);

	// destructor NULL_DELETE(s) grids array and (if initialized) grid dependent and independent data 
	virtual ~MultiGrid();
 
	// initializes grid dependent and independent data and iterative operator
	virtual void  init();

	// solve the problem by the MultiGrid method
	//virtual void  solve(Solution *initialGuess,Solution *result,Real tolerance);

};


class MultiGridIterationStep : virtual public IterationStep
{
protected:

  Integer m_level;
  MultiGrid *m_multiGrid;
	


public: 

	MultiGridIterationStep(Integer level, MultiGrid *mg)
	{
		m_level = level; m_multiGrid = mg;
	}	

	virtual void doIterationStep(Solution *initialGuess,Solution *gridDifference, Solution *result)
	{
		m_multiGrid->mgm(m_level,initialGuess,gridDifference,result);	
	}

};


class MultiGridIterationStepFactory : public Object
{
public:
	static MultiGridIterationStepFactory *getInstance()
	{
		static MultiGridIterationStepFactory *instance = NULL;
		if(!instance) 
			instance = new MultiGridIterationStepFactory();
		return instance;
	}


	IterationStep *createMultiGridIterationStep(Integer level,MultiGrid *mg)
	{
		return new MultiGridIterationStep(level,mg);
	}

};


#endif
