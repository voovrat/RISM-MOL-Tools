#ifndef OPLSAARules_h
#define OPLSAARules_h

#include "MixingRules.h"

class OPLSAARules : public MixingRules
{
protected:
	OPLSAARules()	{}
	

public:

	static OPLSAARules *getInstance()
	{ 	
		static OPLSAARules *instance=NULL;
		if(!instance) instance = new OPLSAARules();
		return instance;
	}

	virtual void operator()(Real sigma1,
				Real epsilon1, 
				Real sigma2,
				Real epsilon2,
				Real *sigma12,
				Real *epsilon12
			);
};

#endif
