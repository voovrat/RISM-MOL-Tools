#ifndef ArrayParameter_h
#define ArrayParameter_h

#include <stdio.h>
#include "Parameter.h"
#include <vector>

class ArrayParameter : public Parameter
{
protected:
	std::vector<Parameter *> m_data;
public:

        ArrayParameter() {}

        ~ArrayParameter() {}

	virtual Integer getType()
	{
		return ARRAY;
	}

	virtual Parameter *clone();
	virtual Parameter *retainCopy();


	std::vector<Parameter *> *getData() 
	{
		return &m_data;
	}

	std::string toString();

};

#endif
