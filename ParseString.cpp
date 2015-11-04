#include "ParseString.h"

#include <string.h>
#include "ParseStringChar.h"
#include "StringParser.h"
#include "ParseName.h"

void ParseString::getString(char *dst,Integer maxLen)
{
	strncpy(dst,m_string,maxLen);
}

Integer ParseString::parse(StringParser *sp)
{

        ParseName parseName;

        if(expectStatement(sp,&parseName))
	{
		parseName.getString(m_string,256);
                return 1;
	}

	char quote = sp->getCurrentChar();
	if(!expectChars(sp,"\'\"")) return 0;	

	ParseStringChar stringChar(quote);
	
	Integer i=0;
	while(stringChar(sp))
	{
		m_string[i]=stringChar.getChar();
		m_string[i+1]=0;
		i++;
	}

	if(!expectChar(sp,quote)) return 0;

	m_string[i]=0;

	return 1;	
	
}
