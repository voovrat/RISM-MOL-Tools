#ifndef ParseSequence_h
#define ParseSequence_h

#include "Settings.h"

#include "ParseStatement.h"
#include "ParseStatementFactory.h"
#include <list>


class ParseSequence : public ParseStatement
{
public:
	const char *m_delimiters;
	Integer m_allowCommentsInside;	
	ParseStatementFactory *m_factory;

	std::list<ParseStatement *> m_statements;

public:
	ParseSequence(	ParseStatementFactory *parseStatementFactory,
			const char *delimiters=" \t\n",
			int allowCommentsInside=1) : ParseStatement("") 
	{
		m_delimiters = delimiters;
		m_allowCommentsInside = allowCommentsInside;
		m_factory = parseStatementFactory;
	}

	// remove all values in m_statements (if any) by NULL_DELETE.
	// if one want to save the list of statements, he need to retain() every element of the list and 
	// copy the pointers to another list.
	virtual ~ParseSequence();

	std::list<ParseStatement *> *getStatements()
	{
		return &m_statements;
	}

	virtual Integer parse(StringParser *sp);


	// one should over load this function.
	// standard behavior is to store ParseStatements into the list
	// parseStatement will be NULL_DELETED in parsing process, so to store it - use retain().
  	// if you do not need to store statements - just re-write elaborate() function without push_back and retain
	virtual void elaborateStatement(ParseStatement *parseStatement)
	{
		parseStatement->retain();
		m_statements.push_back(parseStatement);
	}

	
};




#endif


