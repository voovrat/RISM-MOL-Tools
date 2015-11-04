#ifndef Solution_h
#define Solution_h

// Solution contains the solution approximation on some grid.
// Solution is an abstract class, concrete implementations shopuld be derived from it.


#include "Grid.h"
#include "Object.h"
#include "throwError.h"

class Solution : public Object {

  protected:
         
        Grid *m_grid; // grid on which solution is defined

       
  public:
     
        // Constructor initiailizes Grid. Derived classes should run this constructor in their constructors
	Solution(Grid *grid)
        {  m_grid = grid; 
	}

        // Empty virtual desctructor
	virtual ~Solution() {}

        // Returns the grid on which the solution is defined
        Grid *getGrid() {return m_grid;}

	virtual void *getData()=0;    
	virtual Integer  getDataSize()=0;

        // copy solution to the given destination.
        // function does not allocate the memory. 
        // result should be allocated before.    
        virtual void copy(Solution *dst)=0; // dst=this


        // creates an empty solution of derived class.
        // typical implementation: 
        //  class S: Solution { ... };
        //  S::factory(Grid *g) {return new S(g);}
     // DEPRECATED   virtual Solution *factory(Grid *)=0;  

         //creates a new Grid object and copies there the existing one
        //Solution *clone() 
        //{  Solution *r = factory(m_grid);
        //  copy(r); 
        //  return r;
        //}

	// returns the Zero solution on the grid "grid"
	virtual Solution *setZero()=0;
 
}; 

#define SolutionBinaryOperation(fnname,SolutionType,DataType,operation)	\
void fnname(Solution *x, Solution *y)					\
{									\
	DataType *src,*dst;						\
									\
	SolutionType *goodX = dynamic_cast<SolutionType *>(x);		\
	SolutionType *goodY = dynamic_cast<SolutionType *>(y);		\
									\
	if(!goodX || !goodY)						\
		throwError( #fnname " : incorrect class of arguments");	\
									\
	if(!goodX->getData())						\
		throwError( #fnname " : x is uninitialized");		\
									\
	dst = (DataType *)goodX->getData();				\
									\
	if(!goodY->getData())						\
		throwError( #fnname " : y is uninitialized");			\
									\
	src = (DataType *)goodY->getData();				\
									\
	Integer MN = goodX->getDataSize();				\
	if(goodY->getDataSize() != MN)					\
		throwError( #fnname " sizes of data should be equal");	\
									\
	while(MN)							\
	{								\
		operation;						\
		src++; dst++;						\
		MN--;							\
	} 								\
}

#define SolutionUnaryOperation(fnname,SolutionType,DataType,operation)	\
void fnname(Solution *x)						\
{									\
	DataType *dst;							\
									\
	SolutionType *goodX = dynamic_cast<SolutionType *>(x);		\
									\
	if(!goodX )							\
		throw #fnname " : incorrect class of arguments";	\
									\
	if(!goodX->getData())						\
		throw #fnname " : x is uninitialized";			\
									\
	dst = (DataType *)goodX->getData();				\
									\
	Integer MN = goodX->getDataSize();					\
									\
	while(MN)							\
	{								\
		operation;						\
		dst++;							\
		MN--;							\
	} 								\
}


#define SolutionScalarOperation(fnname,SolutionType,DataType,ScalarDataType,operation)	\
void fnname(Solution *x, ScalarDataType lambda)				\
{									\
	DataType *dst;							\
									\
	SolutionType *goodX = dynamic_cast<SolutionType *>(x);		\
									\
	if(!goodX )							\
		throw #fnname " : incorrect class of arguments";	\
									\
	if(!goodX->getData())						\
		throw #fnname " : x is uninitialized";			\
									\
	dst = (DataType *)goodX->getData();				\
									\
	Integer MN = goodX->getDataSize();					\
									\
	while(MN)							\
	{								\
		operation;						\
		dst++;							\
		MN--;							\
	} 								\
}


class SolutionFactory : public Object
{
public:

	virtual Solution *createSolution(Grid *)=0;
};





#endif
