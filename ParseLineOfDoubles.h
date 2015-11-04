#ifndef ParseLineOfDoubles_h
#define ParseLineOfDoubles_h

#include <list>

#include "ParseStatement.h"
#include "StringParser.h"

class ParseLineOfDoubles : public ParseStatement
{
protected:
	std::list<double> *m_line;

public:
	ParseLineOfDoubles(std::list<double> *line) : ParseStatement("lineOfDoubles")
	{
		m_line = line;
	}

	virtual std::list<double> *getLine()
	{
		return m_line;
	}


	virtual Integer parse(StringParser *sp);

};


#endif
