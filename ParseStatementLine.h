#ifndef ParseStatementLine_h
#define ParseStatementLine_h

#include "ParseStatement.h"
#include "ParseStatementFactory.h"
// Parse line of coma separated statements

#include <list>

class ParseStatementLine : public ParseStatement
{
protected:
	ParseStatementFactory *m_statementFactory;
	std::list<ParseStatement *> m_statements;
	const char *m_delimiters;
	const char *m_eol;

public:
	ParseStatementLine(	ParseStatementFactory *statementFactory,
				const char *delimiters=" \t,",
				const char *EOL="\n"
			)
	: ParseStatement("lineOfStatements")
	{
		m_statementFactory = statementFactory;
		m_delimiters = delimiters;
		m_eol=EOL;
	}

	virtual ~ParseStatementLine();

	void clearStatementList();


	std::list<ParseStatement *> *getStatements()
	{
		return &m_statements;
	}

	virtual Integer parse(StringParser *sp);

};


#endif
