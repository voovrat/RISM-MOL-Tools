#ifndef ParseComment_h
#define ParseComment_h

#include "ParseStatement.h"
#include "StringParser.h"

class ParseComment : public ParseStatement
{
protected:
	const char *m_commentSymbols;

public:
	ParseComment(const char *commentSymbols = "#") : ParseStatement("comment")
	{
		m_commentSymbols = commentSymbols;
	}


	virtual Integer parse(StringParser *sp)
	{Integer ok;
		do{ 	ok=0;

			sp->skipSpace();
			if(!expectChars(sp,m_commentSymbols)) break;
			sp->skipUntil("\n");

			ok=1;			
		}while(0);

		return ok;
	}

};


#endif
