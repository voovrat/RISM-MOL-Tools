#ifndef ParseSpaceString_h
#define ParseSpaceString_h

#include "ParseStatement.h"
#include "ParseString.h"
#include "ParseWord.h"

// Parses string either space-delimited or in quotes

class ParseSpaceString : public ParseStatement 
{
protected:

	ParseString m_parseString;
	ParseWord   m_parseWord;
	Integer m_isWord;

public:

	ParseSpaceString() : ParseStatement("spaceString")
	{
	}

	virtual Integer parse(StringParser *sp)
	{
		if(expectStatement(sp, &m_parseString))
		{
			m_isWord = 0;
			return 1;
		}
		if(!expectStatement(sp, &m_parseWord))
		{
			return 0;
		}
		m_isWord = 1;
		return 1;
	}

	virtual void getString(char *str, int N)
	{
		if(m_isWord) m_parseWord.getString(str,N);
		else m_parseString.getString(str,N);
	}

};

#endif
