#ifndef ParseNonSpace_h
#define ParseNonSpace_h

#include "ParseStatement.h"
#include "StringParser.h"

// parse sequence of non-space chars

class ParseNonSpace : public ParseStatement
{
public:
	char m_string[1024];
public:
	ParseNonSpace()
		: ParseStatement("nonSpace")
	{
	}

	virtual Integer parse(StringParser *sp)
	{
		int i;
		char *ptr;
		for(	i=0, ptr=m_string; i<1024;  i++, ptr++)
		{
			if(sp->currentCharIs(" \t\n")) break;
			*ptr = sp->getChar();
		}
		*ptr=0;
		return (i>0);
	}

};


#endif
