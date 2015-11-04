#include "ParseStatement.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "StringParser.h"


ParseStatement::ParseStatement(const char *name)
{
	strcpy(m_name,name);
	m_expected[0]=0;
	m_errorPos = NULL;

}

char *ParseStatement::getName()
{
	return m_name;
}

char *ParseStatement::getErrorPos()
{
	return m_errorPos;
}

void ParseStatement::fillExpected(StringParser *sp,const char c)
{
	char str[2];
	str[0]=c;str[1]=0;
	fillExpected(sp,str);
}

void ParseStatement::fillExpected(StringParser *sp,const char *str,const char *prefix)
{

		sprintf(m_expected,"%s : %s %s",getName(),prefix,str);
		m_errorPos = (char *)sp->getPtr();

}

void ParseStatement::getExpected(char *dst,Integer maxLen)
{
	strncpy(dst,m_expected,maxLen);
}


Integer ParseStatement::expectChar(StringParser *sp,char C)
{
	
	//m_subExpected = NULL;
	Integer result = sp->getCurrentChar()==C;
	if(result) sp->getChar();

	fillExpected(sp,C);

	return result;  
}

Integer ParseStatement::expectChars(StringParser *sp,const char *chars)
{
	Integer result=sp->currentCharIs(chars);


	fillExpected(sp,chars);

	if(result) sp->getChar();

	m_errorPos = (char *)sp->getPtr();

	return result;

}

Integer ParseStatement::expectRange(StringParser *sp,const char from,const char to)
{
	char c=sp->getCurrentChar();

	
	char str[4];
	str[0]=from;
	str[1]='-';
	str[2]=to;
	str[3]=0;

	fillExpected(sp,str);

	Integer result = (c>=from)&&(c<=to);	

	if(result) sp->getChar();

	return result;
}

Integer ParseStatement::expectStatement(StringParser *sp,ParseStatement *statement)
{	
	Integer result = (*statement)(sp);
//	sprintf(m_expected,"%s : %s",getName(),statement->m_expected);
//	m_subExpected = statement;

//	m_errorPos = sp->getPtr();
	//m_errorPos = statement->getErrorPos();
	if(statement->getErrorPos() > m_errorPos)	
	{	fillExpected(sp,statement->m_expected,"");
		m_errorPos =  statement->getErrorPos();
	}

	return result;	 
}

Integer ParseStatement::isAlpha(const char c)
{
	return ((c>='a') && (c<='z')) || ((c>='A') && (c<='Z'));
}

Integer ParseStatement::isNumeric(const char c)
{
	return (c>='0') && (c<='9');
}

Integer ParseStatement::isAlphaNumeric(const char c)
{
	return isAlpha(c) || isNumeric(c);
}

Integer ParseStatement::operator()(StringParser *sp)
{
	char *ptr = (char *)sp->getPtr();
	m_errorPos = (char *)sp->getPtr();
	if(!parse(sp))
	{

		sp->setPtr(ptr);
		return 0;
	}	
	
	return 1; 
}


