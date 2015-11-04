#ifndef ExtendSolution3DRISM_h
#define ExtendSolution3DRISM_h

#include "BinaryOperation.h"
#include "extendSolution3DRISMRGrid2Grid.h"

class ExtendSolution3DRISM : public BinaryOperation<Solution *>
{
public:
	virtual void operator()(Solution *src,Solution *dst)
	{
		extendSolution3DRISMRGrid2Grid((Solution3DRISMR *)src,(Solution3DRISMR *)dst);
	}

};


#endif
