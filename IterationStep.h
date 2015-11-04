#ifndef IterationStep_h
#define IterationStep_h

#include "IterationDivergeException.h"

class Operator;
class Solution;

class IterationStep  : public Object 
{
public:

//	IterationStep(Object *ptrToKill,Integer shouldKill) 
//	: Chain(ptrToKill,shouldKill) 
//	{}

// CHAIN is deprecated. Use Object::addToDeleteList() instead

	virtual ~IterationStep() {}

	virtual void doIterationStep(Solution *guess,Solution *gridDifference, Solution *result)=0;

	virtual void reset() {}
	
	virtual void onIterationDiverge(IterationDivergeException *exception)
	{
		throw exception;
	}

};

class IterationStepFactory : public Object
{
public:
	virtual IterationStep *createIterationStep(Operator *)=0;

};

#endif
