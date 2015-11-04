#ifndef ParseAtomPattern_h
#define ParseAtomPattern_h

#include "Settings.h"

#include "ParseStatement.h"

class AtomPattern;
class ParseStatementLine;
class AtomPatternArray;
class ParseForceFieldName;

//  Element(index)T
// T - optional, means "Terminal"

#include <list>
#include <vector>

class ParseAtomPattern : public ParseStatement
{
protected:

	Integer m_maxPattern;
	char m_patternName[256];

	std::list<ParseStatementLine *> m_lines;
	std::list<ParseForceFieldName *> m_forceFieldNames;
public:
	ParseAtomPattern();

//	: ParseStatement("atomPattern")
//	{ 	m_patternName[0]=0;
//		m_maxPattern = 0;
//	}

	virtual ~ParseAtomPattern();

	void clearLines();

//	void getElement(char *str,Integer maxLen);
	const char *getPatternName()
	{
		return m_patternName;
	}

	void getPatternName(char *dst,int N);

	Integer getMaxPattern()
	{
		return m_maxPattern;
	}

	virtual Integer parse(StringParser *sp);

	void toAtomPatternArray( AtomPatternArray *patternArray); // out

};



#endif


