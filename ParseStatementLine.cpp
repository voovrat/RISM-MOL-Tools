#include "ParseStatementLine.h"
#include "StringParser.h"

ParseStatementLine::~ParseStatementLine()
{
clearStatementList();
}

void ParseStatementLine::clearStatementList()
{
	std::list<ParseStatement *>::iterator it;
	for(it=m_statements.begin(); it!=m_statements.end(); it++)
	{
		delete *it;
	}

	m_statements.clear();
}

Integer ParseStatementLine::parse(StringParser *sp)
{

	clearStatementList();

	while(1)
	{
		sp->skipChars(m_delimiters);
		ParseStatement *parseStatement = m_statementFactory->createParseStatement();
		m_statements.push_back(parseStatement);

		if(!expectStatement(sp,parseStatement))
		{
			clearStatementList();
			return 0;
		}

		sp->skipChars(m_delimiters);

		if(expectChars(sp,m_eol) || sp->isOver() )
		{
			return 1;
		}
	}

}

/*
#include "ParseAtom.h"

main()
{
SimpleParseStatementFactory<ParseAtom> factory;
ParseStatementLine parseLine(&factory);

const char *str = "C(1)  H(2) H(3) C(4)T C(5)T\n";
StringParser sp(str);

parseLine.parse(&sp);

std::list<ParseStatement *>::iterator it;
std::list<ParseStatement *> *statementList;

statementList = parseLine.getStatements();

for(it = statementList->begin(); it!=statementList->end(); it++)
{
	ParseAtom *parseAtom = (ParseAtom *)*it;
	printf("%s %d %c\n",parseAtom->getElement(),parseAtom->getLabel(),parseAtom->isTerminal() ? 'T' : '@') ;
}


}
*/

