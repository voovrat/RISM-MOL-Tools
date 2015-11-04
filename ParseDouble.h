#ifndef ParseDouble_h
#define ParseDouble_h

#include "ParseStatement.h"

class ParseDouble : public ParseStatement
{
protected:
	Real m_value;
public:
	ParseDouble()
	: ParseStatement("real number") 
	{ m_value=0;}

	Real getDouble()
	{
		return m_value;
	} 

	virtual Integer parse(StringParser *);

};

#endif
