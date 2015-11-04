#ifndef LorentzBerthelotRules_h
#define LorentzBerthelotRules_h

#include "MixingRules.h"

class LorentzBerthelotRules : public MixingRules
{
protected:
	LorentzBerthelotRules() {}
public:
	static LorentzBerthelotRules *getInstance()
	{ 	
		static LorentzBerthelotRules *instance=NULL;
		if(!instance) instance = new LorentzBerthelotRules();
		return instance;
	}


	virtual void operator()(
				Real sigma1,
				Real epsilon1, 
				Real sigma2,
				Real epsilon2,
				Real *sigma12,
				Real *epsilon12
			);

};


#endif
