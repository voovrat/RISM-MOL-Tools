#ifndef PLHNCClosure3DRISM_h
#define PLHNCClosure3DRISM_h

#include "Closure3DRISM.h"

class Solution3DRISMR;

class PLHNCClosure3DRISM : public Closure3DRISM
{
	Solution3DRISMR *m_betaUShort;
	
public:
	PLHNCClosure3DRISM( Solution3DRISMR *betaUshort);

	virtual ~PLHNCClosure3DRISM() {}

	virtual void calculateClosure(	Solution3DRISMR *gamma,
					Solution3DRISMR *c //out
					);

};

class PLHNCClosureFactory3DRISM : public ClosureFactory3DRISM
{
public:

	virtual Closure3DRISM *createClosure3DRISM(Solution3DRISMR *betaUshort)
	{
		return new PLHNCClosure3DRISM(betaUshort);
	}
};

#endif
