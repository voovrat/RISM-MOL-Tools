#ifndef DoubleParameter_h
#define DoubleParameter_h

#include <stdio.h>
#include "Parameter.h"

class DoubleParameter : public Parameter
{
public:

	virtual Integer getType()
	{
		return DOUBLE;
	}

	virtual Real getDouble() {}
	virtual void setDouble(Real)=0;

	virtual Parameter *clone()=0;

	std::string toString()
	{
		char s[256];
		sprintf(s,"%lf",getDouble());
		return s;
	}
};

#endif
