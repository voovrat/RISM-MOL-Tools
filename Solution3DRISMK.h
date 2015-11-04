#ifndef Solution3DRISMK_h
#define Solution3DRISMK_h

// Solution contains the solution approximation on some grid.
// Solution is an abstract class, concrete implementations shopuld be derived from it.

#include "Grid3DRISM.h"
#include "Solution.h"
//#include "matrix.h"
#include <complex>
#include "TraceAllocations.h"
#include "Settings.h"

#include "SolutionRISM.h"

using namespace std;

//class GridDependent1DRISMMatlab;

class Solution3DRISMK : public SolutionRISM<complex<Real> > 
{

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

		return g3d->getNx() * g3d->getNy() * ( g3d->getNz()/2 + 1);
	}

  public:
     
        // Constructor initiailizes Grid. Derived classes should run this constructor in their constructors
	Solution3DRISMK(Grid *grid,Integer numberOfSolventSites)
	: SolutionRISM<complex<Real> >(grid,numberOfSolventSites)
 	{
#if DEBUG_LEAKS
	m_allocID=m_traceAllocations.traceAlloc(Solution3DRISMK::calculateGammaSize() * numberOfSolventSites * sizeof(Real),this);
#endif


	}

	virtual ~Solution3DRISMK()
	{
#if DEBUG_LEAKS
	m_traceAllocations.traceDealloc(getTotalSizeOfGamma()*sizeof(Real),this,m_allocID);	
#endif
	}

}; 

class SolutionFactory3DRISMK : public SolutionFactoryRISM<complex<Real> >
{
protected:

	SolutionRISM<complex<Real> > * newSolutionRISM(Grid *grid)
	{
		return new Solution3DRISMK(grid,m_numberOfSites);
	}

public:
	SolutionFactory3DRISMK(Integer numberOfSolventSites)
	: SolutionFactoryRISM<complex<Real> >(numberOfSolventSites)
	{
	}

	
};

	// add two solutions. Data is not alocated in the function.
        // function works as: x = x +y
   void addSolution3DRISMK(Solution *x, Solution *y);    // x = x + y

	// subtract two solutions. Data is not alocated in the function.
        // function works as: x = x -y
   void subSolution3DRISMK(Solution *x,Solution *y);    // x= x - y;

	// subtract two solutions. Data is not alocated in the function.
        // function works as: x = x -y
   void mulSolution3DRISMK(Solution *x,Solution *y);    // x= x * y;

	// subtract two solutions. Data is not alocated in the function.
        // function works as: x = x -y
   void divSolution3DRISMK(Solution *x,Solution *y);    // x= x / y;

 	// multiply solution by the scalar:  x =x*lambda
   void addScalarSolution3DRISMK(Solution *x,Real lambda);  // x = x * lambda

	// multiply solution by the scalar:  x =x*lambda
   void subScalarSolution3DRISMK(Solution *x,Real lambda);  // x = x * lambda

	// multiply solution by the scalar:  x =x*lambda
   void mulScalarSolution3DRISMK(Solution *x,Real lambda);  // x = x * lambda

	// multiply solution by the scalar:  x =x*lambda
   void divScalarSolution3DRISMK(Solution *x,Real lambda);  // x = x * lambda



#define KGAMMA_FOR_SOLUTION(solution,gamma_id)				      \
{complex<Real> *KGAMMA_FOR_ptr = ((Solution3DRISMK*)solution)->getGamma()[gamma_id];  \
KGAMMA_FOR(solution->getGrid())						      \

#define KGAMMA_FOR_DATA *KGAMMA_FOR_ptr

#define END_KGAMMA_FOR_SOLUTION   KGAMMA_FOR_ptr++;} END_KGAMMA_FOR


#endif
