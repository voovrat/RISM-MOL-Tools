#include "ParseSequence.h"

#include "ParseComment.h"

ParseSequence::~ParseSequence()
{

std::list<ParseStatement *>::iterator it;
for(it=m_statements.begin(); it!=m_statements.end(); it++)
{
	NULL_DELETE(*it);
}

m_statements.clear();

}

Integer ParseSequence::parse(StringParser *sp)
{

ParseComment parseComment;

while(1)
{
	sp->skipChars(m_delimiters);
	if(sp->isOver()) return 1;

	do{	
		if(expectStatement(sp,&parseComment) && m_allowCommentsInside ) break;

		ParseStatement *parseStatement = m_factory->createParseStatement();
	
		int result = expectStatement(sp,parseStatement);

		if(result) elaborateStatement(parseStatement);
			
		NULL_DELETE(parseStatement);

		if(result) break;

		return 1;
	}while(0);

}

}


