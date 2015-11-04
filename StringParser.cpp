#include "StringParser.h"

#include <stdlib.h>
	
StringParser::StringParser(const char *string)
{
	m_ptr = string;
	m_error = 0;
}

Integer StringParser::isCharInString(char c,const char *str)
{
	for(;*str;str++)
		if(c==*str) return 1;

	return 0;
}

void StringParser::skipChars(const char *chars)
{
//	if(!isCharInString(*m_ptr,chars)) m_error=1;

	for(;*m_ptr && isCharInString(*m_ptr,chars); m_ptr++) ;
}


void StringParser::skipSpace()
{
	skipChars(" \t\n");
}


void StringParser::skipEOL()
{
		skipChars("\n\r");
}

void StringParser::skipUntil(const char *delim)
{
	while(*m_ptr && !isCharInString(*m_ptr,delim)) m_ptr++;
}

Real 	StringParser::getDouble()
{
	char *endptr;
	Real d=strtod(m_ptr,&endptr);
	
	m_error = (endptr == m_ptr);
	m_ptr = endptr;
	
	return d;
}


Integer 	StringParser::getInt()
{
	char *endptr;
	long l=strtol(m_ptr,&endptr,10);
	
	m_error = (endptr == m_ptr);
	m_ptr = endptr;
	
	return (Integer)l;
}


char	StringParser::getChar()
{
	char c=0;

	if(*m_ptr == 0)	m_error=1;
	else 
	{ 
		c = *m_ptr;
		m_ptr++;
	}

	return c;
}

void 	StringParser::getUntil(const char *delim,char *str,Integer N)
{
	for(;*m_ptr && !isCharInString(*m_ptr,delim) && N>0; 
	    m_ptr++, str++, N--)
	{
		*str = *m_ptr;
	}
}


void 	StringParser::getWord(char *word,Integer maxChar)
{
	getUntil(" \t\n.,",word,maxChar);
}

void 	StringParser::getLine(char *line,Integer maxChar)
{
	getUntil("\n",line,maxChar);
}
	

