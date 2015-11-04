#ifndef Operator_h
#define Operator_h

//#include "Solution.h"
//#include "GridDependentData.h"
//#include "GridIndependentData.h"

class Solution;
class GridDependentData;
class GridIndependentData;

// Interface (function pointer) for the Operator function. 
// Operator F perform the action y=F(x).
// Input arguments:
//  - solution x
//  - GridDependent and GridIndependent data (see corresponding h-files for description)
//  - the last argument is result y. 
//    Result Solution should be allocated BEFORE the Operator runs.
//    Operator does not do any memory allocations... 

#include "Object.h"

class Operator : public Object
{
protected:
	GridIndependentData *m_gridIndependent;
	GridDependentData *m_gridDependent;

public:

	Operator()
	{
		m_gridIndependent = NULL;
		m_gridDependent = NULL;
	}

	virtual GridDependentData *getGridDependent()
	{
		return m_gridDependent;
	}

	virtual GridIndependentData *getGridIndependent()
	{
		return m_gridIndependent;
	}

	Operator(GridIndependentData *gridIndependent, GridDependentData *gridDependent)
	{
		m_gridIndependent = gridIndependent;
		m_gridDependent = gridDependent;
	}

	virtual void F(Solution *x,Solution *result)=0;		// result = F(x)

};

class OperatorFactory : public Object
{
public:
	
	virtual Operator *createOperator(GridIndependentData *,GridDependentData *)=0;
};

#endif
