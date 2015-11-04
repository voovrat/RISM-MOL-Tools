#ifndef Solution3DRISMR_h
#define Solution3DRISMR_h

// Solution contains the solution approximation on some grid.
// Solution is an abstract class, concrete implementations shopuld be derived from it.

#include "SolutionRISM.h"

#include "Grid3DRISM.h"
#include "Solution.h"
//#include "matrix.h"

#include "Settings.h"
#include "TraceAllocations.h"


//class GridDependent1DRISMMatlab;

class Solution3DRISMR : public SolutionRISM<Real> {

//  protected:
         
       // Grid *m_grid; // grid on which solution is defined
  protected:

#if DEBUG_LEAKS
	static TraceAllocations m_traceAllocations;
	Integer m_allocID;
#endif	


 	virtual Integer calculateGammaSize()
	{
		Grid3DRISM *g3d = dynamic_cast<Grid3DRISM*>(m_grid);
		
		if(!g3d)
			throw "Solution3DRISMR::calculateGammaSize : invalid grid class";

		return g3d->getNx() * g3d->getNy() * g3d->getNz();
	}
  public:
     
        // Constructor initiailizes Grid. Derived classes should run this constructor in their constructors
	Solution3DRISMR(Grid *grid,Integer numberOfSolventSites)
	: SolutionRISM<Real>(grid,numberOfSolventSites)
	{
#if DEBUG_LEAKS
	m_allocID = m_traceAllocations.traceAlloc(Solution3DRISMR::calculateGammaSize() * numberOfSo);
#endif

	}
	
	virtual ~Solution3DRISMR()
	{
#if DEBUG_LEAKS
	m_traceAllocations.traceDealloc(getTotalSizeOfGamma()*sizeof(Real),this,m_allocID);	
#endif
	}
 
}; 

class SolutionFactory3DRISMR : public SolutionFactoryRISM<Real>
{
protected:

	virtual SolutionRISM<Real> * newSolutionRISM(Grid *grid)
	{
		return new Solution3DRISMR(grid,m_numberOfSites);
	}

public:
	SolutionFactory3DRISMR(Integer numberOfSolventSites)
	: SolutionFactoryRISM<Real>(numberOfSolventSites)
	{
	}

};



// Macro, which checks the classes and sizes of the arguments and give an access to the internal data

	// add two solutions. Data is not alocated in the function.
        // function works as: x = x +y
   void addSolution3DRISMR(Solution *x, Solution *y);    // x = x + y

	// subtract two solutions. Data is not alocated in the function.
        // function works as: x = x -y
   void subSolution3DRISMR(Solution *x,Solution *y);    // x= x - y;

	// subtract two solutions. Data is not alocated in the function.
        // function works as: x = x -y
   void mulSolution3DRISMR(Solution *x,Solution *y);    // x= x * y;

	// subtract two solutions. Data is not alocated in the function.
        // function works as: x = x -y
   void divSolution3DRISMR(Solution *x,Solution *y);    // x= x / y;

 	// multiply solution by the scalar:  x =x*lambda
   void addScalarSolution3DRISMR(Solution *x,Real lambda);  // x = x * lambda

	// multiply solution by the scalar:  x =x*lambda
   void subScalarSolution3DRISMR(Solution *x,Real lambda);  // x = x * lambda

	// multiply solution by the scalar:  x =x*lambda
   void mulScalarSolution3DRISMR(Solution *x,Real lambda);  // x = x * lambda

	// multiply solution by the scalar:  x =x*lambda
   void divScalarSolution3DRISMR(Solution *x,Real lambda);  // x = x * lambda

	// take exponent of solution
   void expSolution3DRISMR(Solution *x);	// x = exp(x);

#define GAMMA_FOR_SOLUTION(solution,gamma_id)				      \
{Real *GAMMA_FOR_ptr = ((Solution3DRISMR*)solution)->getGamma()[gamma_id];  \
GAMMA_FOR(solution->getGrid())						      \

#define GAMMA_FOR_DATA *GAMMA_FOR_ptr

#define END_GAMMA_FOR_SOLUTION   GAMMA_FOR_ptr++;} END_GAMMA_FOR


#endif
