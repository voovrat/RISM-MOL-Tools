#include "MultiGrid.h"
#include <stdio.h>
#include "performNIterationSteps.h"


#include "MGFactoryCollection.h"
#include "Grid.h"
#include "Solution.h"
#include "Solver.h"
#include "GridDependentData.h"


  // construct new MultiGrid object. 
   // needs: zero grid, operations, depth, coarse grid solver. construct grids array
MultiGrid::MultiGrid(Grid *grid0,
   			Operations *operations,
			MGFactoryCollection *factories,
			Integer depth, 
			Integer preSmoothingSteps, 
			Integer postSmoothingSteps,
			Integer numberOfMultiGridSubSteps)
{

//	m_coarseGridSolver = ;
	m_grids = NULL;

	m_operations = operations;
	m_factories = factories;

	m_grid0 = grid0;
	m_depth = depth;
	m_preSmoothingSteps = preSmoothingSteps;
	m_postSmoothingSteps = postSmoothingSteps;
	m_numberOfMultiGridSubSteps = numberOfMultiGridSubSteps;
	
	m_isInited = 0;
}


   // destructor NULL_DELETE(s) grids array and (if initialized) grid dependent and independent data 
MultiGrid::~MultiGrid()
{
	unInit();
}
 
   // function NULL_DELETE(s) grid independent and grid dependent data
 void MultiGrid::unInit()
 {
	Integer i;
	if(!m_isInited) return;
     
	//m_gridIndependent = NULL;

	for(i=0;i<m_depth;i++)
       	{	NULL_DELETE(m_gridDependentData[i]);
		NULL_DELETE(m_grids[i]);
	}
	delete [] m_gridDependentData;
	delete [] m_grids;
	m_gridDependentData = NULL;
	m_grids = NULL;

    	for(i=0;i<m_depth-1;i++)
	{
		NULL_DELETE(m_fineGridIterationSteps[i]);
		NULL_DELETE(m_operators[i]);
	}
	delete [] m_fineGridIterationSteps;
	delete [] m_operators;
	m_fineGridIterationSteps = NULL;
	m_operators = NULL;
	
	NULL_DELETE(m_coarseGridSolver);
 	m_coarseGridSolver = NULL;


	m_isInited = 0;
  }

   // function creates and fills the grids array
Grid **MultiGrid::generateGrids(Grid *grid0,Integer depth, void (*restrictGrid)(Grid *,Grid *))
{    Integer i;

     Grid **grids = new Grid*[depth];
          
     grids[0]=grid0->clone();

     for(i=0; i<depth-1; i++)
     {    grids[i+1]=grid0->factory();
         restrictGrid(grids[i],grids[i+1]);
     }

     return grids;
}

   // initializes grid dependent and independent data and iterative operator
void  MultiGrid::init()
{
	Integer i;

	unInit();

	m_grids = generateGrids(m_grid0,m_depth,m_operations->restrictGrid);

	m_gridDependentData = new GridDependentData *[m_depth];
	m_operators = new Operator*[m_depth];


	for(i=0;i<m_depth;i++)
	{
        	m_gridDependentData[i] = m_factories->createGridDependent(m_grids[i]);
		m_operators[i] = 
				m_factories->createOperator(m_gridDependentData[i]);
	}
 
	m_fineGridIterationSteps = new IterationStep*[m_depth-1];


	for(i=0;i<m_depth-1;i++)
   	{	
		m_fineGridIterationSteps[i] = 
				m_factories->createFineGridIterationStep(m_gridDependentData[i]);
	
   	}

	m_coarseGridSolver = m_factories->createCoarseGridSolver(m_gridDependentData[m_depth-1]);

	m_isInited = 1;
}

void MultiGrid::calculateGridDifference(
			Integer level,
			Solution *fineSolution,
			Solution *fineGridDifference,
			Solution *result )
{
	Solution *FineTmp,*CoarseTmp;

	FineTmp = m_factories->createSolution(m_grids[level]);  
	CoarseTmp = m_factories->createSolution(m_grids[level+1]); 

	// result = Frx

	m_operations->restrictSolution(fineSolution,CoarseTmp); // CoarseTmp=rx
	m_operators[level+1]->F(CoarseTmp ,result); // result = Frx 	
	
	// CoarseTmp = rFx	

	m_operators[level]->F(fineSolution,FineTmp); // FineTmp = Fx
	m_operations->restrictSolution(FineTmp,CoarseTmp); //CoarseTmp = rFx

	// result = Frx - rFx
	
        m_operations->sub(result,CoarseTmp); 

	// CoarseTmp = r GD_fine
	
	m_operations->restrictSolution(fineGridDifference, CoarseTmp);

	// is incorrect. should be vice versa (see bellow)
	// result = Frx - rFx + r GD_fine
	//m_operations->add(result, CoarseTmp );

	// CoarseTmp = rFx - Frx + r GD_fine
	m_operations->sub(CoarseTmp,result );
	CoarseTmp->copy(result);
	

	NULL_DELETE(FineTmp);
	NULL_DELETE(CoarseTmp);
}

  // perform one multi-grid iteration.
void MultiGrid::mgm(Integer level, Solution *initialGuess, Solution *fineGridDifference,Solution *result)
{
	Integer i;

	if(level==m_depth-1)
	{
             	m_coarseGridSolver->solve(initialGuess,fineGridDifference,result);
 	     	return;
	}

	// perform pre-Smoothing iterations

		beforePreSmoothing(level,initialGuess,fineGridDifference);

	Solution *xFine,*yFine;

	xFine = m_factories->createSolution(m_grids[level]);
	yFine = m_factories->createSolution(m_grids[level]);

	performNIterationSteps(	m_preSmoothingSteps,
				m_fineGridIterationSteps[level],
				initialGuess,
				fineGridDifference,
				xFine,
				m_factories->m_solutionFactory);

		afterPreSmoothing(level, xFine);

	// calculate Grid Difference

	Solution *coarseGridDifference; // = initialGuess->factory(m_grids[level+1]);
 	Solution *xCoarse, *yCoarse;


	xCoarse = m_factories->createSolution(m_grids[level+1]);
	yCoarse = m_factories->createSolution(m_grids[level+1]);
	coarseGridDifference = m_factories->createSolution(m_grids[level+1]);

	calculateGridDifference(level,xFine,fineGridDifference,coarseGridDifference);

		afterGridDifference(level,coarseGridDifference);

	//perform Coarse Grid Multi Grid sub Iterations

	m_operations->restrictSolution(xFine,xCoarse);
	
        MultiGridIterationStep subMGM(level+1,this);

		beforeSubIteration(level,xCoarse);

	performNIterationSteps(	m_numberOfMultiGridSubSteps,
				&subMGM,
				xCoarse,
				coarseGridDifference,
				yCoarse,
				m_factories->m_solutionFactory);

		afterSubIteration(level,yCoarse);

	// refine fine-grid solution
        // Gamma_fine = Gamma_fine(0) + p ( Gamma_coarse(n) - Gamma_coarse(0) )
        
	m_operations->sub(yCoarse,xCoarse); // yCoarse = Gamma_coarse(n) - Gamma_coarse(0);
		
	m_operations->interpolateSolution(yCoarse, yFine); // yFine = p  ( Gamma_coarse(n) - Gamma_coarse(0) )
	beforeFineGridCorrection(level,yFine);

	m_operations->add(xFine, yFine); // xFine = Gamma_fine(0) + p( Gamma_coarse(n) - Gamma_coarse(0) )

		afterFineGridCorrection(level,xFine);

	// perform post-smoothing iterations

	performNIterationSteps(	m_postSmoothingSteps,
				m_fineGridIterationSteps[level],
				xFine,
				fineGridDifference,
				result,
				m_factories->m_solutionFactory);


		afterPostSmoothing(level,result);

	NULL_DELETE(xFine);		
	NULL_DELETE(yFine);
	NULL_DELETE(xCoarse);
	NULL_DELETE(yCoarse);
	NULL_DELETE(coarseGridDifference);
		
}

   // solve the problem by the MultiGrid method   
/*
void  MultiGrid::solve(Solution *initialGuess, Solution *result,Real tolerance)
{
	if(!m_isInited) 
	{
		throw "****  Trying to run uninitialized Multi Grid solver! ****\n";
		return;
	}

	Solution *Zero;

	Zero = m_factories->createSolution(m_grids[0]);
	Zero->setZero();	

	MultiGridIterationStep mgIteration();


	mgm(0, initialGuess, Zero , result);

	NULL_DELETE(Zero);
}
*/
   

