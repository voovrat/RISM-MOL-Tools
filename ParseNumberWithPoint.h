#ifndef ParseNumberWithPoint_h
#define ParseNumberWithPoint_h

#include "ParseStatement.h"

class ParseNumberWithPoint : public ParseStatement
{
protected:
	Real m_value;
public:
	ParseNumberWithPoint()
	: ParseStatement("number with poInteger") 
	{ m_value=0;	}

	Real getDouble()
	{
		return m_value;
	}

	virtual Integer parse(StringParser *sp);

};


#endif
