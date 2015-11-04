#ifndef ParseString_h
#define ParseString_h

#include "ParseStatement.h"

class ParseString : public ParseStatement
{
protected:
	char m_string[1024];

public:

	ParseString()
	: ParseStatement("string") {}

	void getString(char *dst,Integer maxLen);
	

	virtual Integer parse(StringParser *sp);
};


#endif
