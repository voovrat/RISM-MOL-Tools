#ifndef ParseUnsigned_h
#define ParseUnsigned_h

#include "ParseStatement.h"

class ParseUnsigned : public ParseStatement
{
	Real m_integer;

public:
	ParseUnsigned()	
	: ParseStatement("unsigned number")
	{
		m_integer =0;
	}

	Real getInteger()
	{
		return m_integer;
	}

	virtual Integer parse(StringParser *sp);

};


#endif
