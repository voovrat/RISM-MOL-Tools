#ifndef HNCClosure3DRISM_h
#define HNCClosure3DRISM_h

#include "Closure3DRISM.h"

class Solution3DRISMR;
class SolutionFactory3DRISMR;

class HNCClosure3DRISM : public Closure3DRISM
{
	SolutionFactory3DRISMR *m_solutionFactory;
	Solution3DRISMR *m_betaUShort;
	
public:
	HNCClosure3DRISM( Solution3DRISMR *betaUshort);

	~HNCClosure3DRISM();

	virtual void calculateClosure(	Solution3DRISMR *gamma,
					Solution3DRISMR *c //out
					);

};

class HNCClosureFactory3DRISM : public ClosureFactory3DRISM
{
public:

	virtual Closure3DRISM *createClosure3DRISM(Solution3DRISMR *betaUshort)
	{
		return new HNCClosure3DRISM(betaUshort);
	}
};

#endif

