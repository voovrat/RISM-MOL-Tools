#include "ParseStringChar.h"

#include "StringParser.h"
#include "ParseSlashedChar.h"


Integer ParseStringChar::parse(StringParser *sp)
{
	ParseSlashedChar slashedChar;

	char c = sp->getCurrentChar();

	if(c=='\\')
	{ 

		if(slashedChar(sp))
		{	m_char = slashedChar.getChar();
			return 1; 
		}
		else return 0;
	}

	if(c==m_quote) 
		return 0;
	if(c=='\n')	
		return 0;

	m_char = sp->getChar();
	return 1;	
}

