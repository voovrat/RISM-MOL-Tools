#ifndef ParseAtomRadiusFile_h
#define ParseAtomRadiusFile_h

#include "ParseAtomRadius.h"
#include "ParseSequence.h"

#include <string>
#include <map>

class ParseAtomRadiusFile : public ParseSequence
{
public:

// inherited
//	const char *m_delimiters;
//	Integer m_allowCommentsInside;	
//	ParseStatementFactory *m_factory;

//	std::list<ParseStatement *> m_statements;

	SimpleParseStatementFactory<ParseAtomRadius> m_factory;
	std::map<std::string,Real> *m_sigmas;

public:
	ParseAtomRadiusFile(std::map<std::string,Real> *sigmas)
	: ParseSequence( &m_factory
			//delimiters=" \t\n", allowCommentsInside=1
			)
	{
		m_sigmas = sigmas;
	}

	std::list<ParseStatement *> *getStatements()
	{
		throw "Do not use ParseAtomRadiusFile::getStatements."	
			" Read m_sigmas map instead";
		return NULL;
	}

	// inherited virtual Integer parse(StringParser *sp);

	// add new elelent to m_sigmas map
	// does not add a new statement to m_statements array
	virtual void elaborateStatement(ParseStatement *parseStatement);

	
};




#endif


