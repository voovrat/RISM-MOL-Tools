#ifndef MixingRules_h
#define MixingRules_h

#include "Object.h"

//Mixing rules for LJ potential
//can be used as a function

class MixingRules : public Object
{
public:
	virtual void operator()(
			Real sigma1,
			Real epsilon1,
			Real sigma2,
			Real epsilon2,
			Real *sigma12,
			Real *epsilon12	)=0;

};

#endif
