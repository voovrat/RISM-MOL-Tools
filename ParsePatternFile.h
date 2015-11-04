#ifndef ParsePatternFile_h
#define ParsePatternFile_h

#include "Settings.h"

#include "ParseSequence.h"
#include <list>
#include <vector>

#include "ParseAtomPattern.h"

class AtomPattern;
class AtomPatternArray;

class ParsePatternFile : public ParseSequence 
{
public:
//inherited
//	const char *m_delimiters;
//	Integer m_allowCommentsInside;	
//	ParseStatementFactory *m_factory;
//not used
//	std::list<ParseStatement *> m_statements;

SimpleParseStatementFactory<ParseAtomPattern> m_patternFactory;

std::list<AtomPatternArray *> *m_patterns;

public:
	ParsePatternFile(std::list<AtomPatternArray *> *patterns)
	: ParseSequence( &m_patternFactory,	//ParseStatementFactory *parseStatementFactory,
			 " \t\n",//const char *delimiters=" \t\n",
			1 //int allowCommentsInside=1
			) 
	{
		m_patterns = patterns;
	}

	std::list<ParseStatement *> *getStatements()
	{
		throw "Do not use this function. Use parse and then read m_patterns list";
		return NULL;
	}

	//virtual Integer parse(StringParser *sp); - inherited form ParseSequence

	// ParseAtomPatterns, convert them to vectors and push_back to the m_patterns
	virtual void elaborateStatement(ParseStatement *parseStatement);
	
};




#endif


