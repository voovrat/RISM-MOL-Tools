#ifndef ParseStringChar_h
#define ParseStringChar_h

#include "ParseStatement.h"

class ParseStringChar : public ParseStatement
{
protected:
	char m_char;
	char m_quote;
	Integer parseSlashChar(char c);

public:

	char getChar()
	{
		return m_char;
	}

	ParseStringChar(char Quote) 
	: ParseStatement("stringChar")
	{
		m_quote=Quote;		
		sprintf(m_name,"[%c]-stringChar",Quote);
	}

	virtual Integer parse(StringParser *sp);
};


#endif
