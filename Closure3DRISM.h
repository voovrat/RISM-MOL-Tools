#ifndef Closure3DRISM_h
#define Closure3DRISM_h

#include "Object.h"

class Solution3DRISMR;

class Closure3DRISM : public Object
{
public:
	virtual void calculateClosure(	Solution3DRISMR *gamma,	
					Solution3DRISMR *c_short	//out
					)=0;
};


class ClosureFactory3DRISM : public Object
{
public:

	virtual Closure3DRISM *createClosure3DRISM(Solution3DRISMR *betaUshort)=0;
};

#endif
