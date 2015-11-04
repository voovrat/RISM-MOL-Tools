#ifndef SolutionRISM_h
#define SolutionRISM_h


// Solution contains the solution approximation on some grid.
// Solution is an abstract class, concrete implementations shopuld be derived from it.

#include "Grid3DRISM.h"
#include "Solution.h"
//#include "matrix.h"


//class GridDependent1DRISMMatlab;
template<class T>
class SolutionRISM : public Solution {

//  protected:
         
       // Grid *m_grid; // grid on which solution is defined
  protected:
	
//	mxArray * m_data;
	T **m_gamma;
	T *m_rawData;

	Integer m_numberOfSites;
//	Integer *m_siteMultiplicities;

	Integer m_N;
	Integer m_MN;

	void cleanUp();

	virtual Integer calculateGammaSize()=0;

  public:
     
        // Constructor initiailizes Grid. Derived classes should run this constructor in their constructors
	SolutionRISM(Grid *grid,Integer numberOfSites);
	virtual ~SolutionRISM();

	void createGamma();
	void setGamma(T **gamma);
	
	T **getGamma();
	T *getRawData()
	{
		return m_rawData;
	}
	
	Integer getSizeOfOneGamma()
	{
		return m_N;
	}

	Integer getTotalSizeOfGamma()
	{
		return m_MN;
	}

	virtual void *getData()
	{
		return getRawData();
	}

	virtual Integer getDataSize()
	{
		return getTotalSizeOfGamma();
	}
	
	// resulting array should be destroyed by user with mxDestroyArray() 
//	mxArray *calculateC(GridDependent1DRISMMatlab *gridDependent);

	Integer getNumberOfSites() 
	{
		return m_numberOfSites;
	}
    
        // copy solution to the given destination.
        // function does not allocate the memory. 
        // result should be allocated before.    
        virtual void copy(Solution *dst); // dst=this


	// returns the Zero solution on the grid "grid"
	virtual Solution *setZero();

//	void plot(GridDependent1DRISMMatlab *);
 
}; 

template<class T>
class SolutionFactoryRISM : public SolutionFactory
{
protected:
	Integer m_numberOfSites;

	virtual SolutionRISM<T> * newSolutionRISM(Grid *grid)=0;
	

public:
	SolutionFactoryRISM(Integer numberOfSites)
	{
		m_numberOfSites = numberOfSites;
	}

	Solution *createSolution(Grid *grid)
	{
		Grid *g1 = grid->clone();

		SolutionRISM<T> *S = newSolutionRISM(g1);
		S->addToDeleteList(g1);
		S->createGamma();
		return S;
	}
};


#endif
