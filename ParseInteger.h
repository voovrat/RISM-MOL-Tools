#ifndef ParseInteger_h
#define ParseInteger_h

#include "ParseStatement.h"

class ParseInteger : public ParseStatement
{
	Real m_integer;
	Integer m_sign;

public:
	ParseInteger()	
	: ParseStatement("integer number")
	{
		m_integer =0;
	}

	Real getInteger()
	{
		return m_integer;
	}

	Integer getSign()
	{
		return m_sign;
	}

	virtual Integer parse(StringParser *sp);

};


#endif
