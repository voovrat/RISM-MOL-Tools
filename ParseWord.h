#ifndef ParseWord_h
#define ParseWord_h

#include "ParseStatement.h"

// parse word until delimiter

class ParseWord : public ParseStatement
{
public:
	char m_string[256];
	const char *m_delimiters;
public:
	ParseWord(const char *delimiters="\t\n ") : ParseStatement("word")
	{
		m_delimiters = delimiters;
	}
		
	
	virtual Integer parse(StringParser *sp);

	void getString(char *str,int N);
};


#endif
