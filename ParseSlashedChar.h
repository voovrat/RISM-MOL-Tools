#ifndef ParseSlashedChar_h
#define ParseSlashedChar_h

#include "ParseStatement.h"
#include "StringParser.h"

class ParseSlashedChar : public ParseStatement
{
protected:
	char m_char;

public:
	ParseSlashedChar()
	: ParseStatement("slashed char")
	{ m_char = 0; }

	char getChar()
	{
		return m_char;
	}

	virtual Integer parse(StringParser *sp)
	{
		if(!expectChar(sp,'\\')) return 0;

		char c=sp->getCurrentChar();

		if(!expectChars(sp,"nt\"\'\\")) return 0;

		switch(c)
		{
			case 'n': m_char='\n';break;
			case 't': m_char='\t';break;
			case '\"': m_char='\"';break;
			case '\'': m_char='\'';break;
			case '\\': m_char='\\';break;
		};

		return 1;
		
	}

};


#endif
