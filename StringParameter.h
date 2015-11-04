#ifndef StringParameter_h
#define StringParameter_h

#include "Parameter.h"
#include <string.h>

class StringParameter : public Parameter
{
protected:

	char *m_string;

public:
	virtual Integer getType()
	{
		return STRING;
	}
	
	virtual ~StringParameter();



	StringParameter(const char *string);
	virtual void getString(char *dst,Integer maxLen);
	virtual const char *getStringPtr() 
	{
		return m_string;
	}	


	virtual Parameter *clone()
	{
		return new StringParameter(m_string);
	}

	static std::string slashify(const char *s);

	std::string toString()
	{
		return '\"' + slashify(m_string) + '\"';
	}

};

#endif
