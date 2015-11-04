#ifndef ParseName_h
#define ParseName_h

#include "ParseStatement.h"

class ParseName : public ParseStatement
{
protected:
	char m_string[256];

public:
	ParseName()
	: ParseStatement("name")
	{ m_string[0]=0; }

	void getString(char *str,Integer maxLen);

	Integer expectFirstNameChar(StringParser *sp);
	Integer expectNameChar(StringParser *sp);

	virtual Integer parse(StringParser *sp);

};


#endif
