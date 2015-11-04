#ifndef Norm_h
#define Norm_h

#include "Object.h"

class Norm : public Object
{
public:

	virtual Real calculateNorm(Object *x,Object *y)=0;
	
};


#endif
