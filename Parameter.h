#ifndef Parameter_h
#define Parameter_h

#include "Object.h"
#include "Exception.h"
#include <string>

class Parameter : public Object
{
public:

	enum Type
	{
		STRING,
		DOUBLE,
                PAIR,
		ARRAY
	};
	

	virtual Integer getType()
	{
		throw new Exception(this,"Parameter is a base class and has no type");
	}

	virtual Real getDouble()
	{
		throw new Exception(this,"Parameter : Parameter is not a Real!");
	}

	virtual void getString(char *string, Integer maxLen)
	{
		throw new Exception(this,"Parameter: Parameter is not a  string!");	
	}

	virtual const char *getStringPtr()
	{
		throw new Exception(this,"Parameter: Parameter is not a string!");
	}

	virtual Parameter *clone()
	{
		throw new Exception(this,"Parameter: base parameter should not be cloned!");
	}

	virtual Parameter *retainCopy()
	{
		this->retain();
		return this;
	}


	virtual std::string toString()
	{
		throw new Exception(this,"Parameter: base parameter have no string representation!");
		return "";
	}

};

#endif
