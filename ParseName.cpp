#include "ParseName.h"

#include <string.h>
#include "StringParser.h"


void ParseName::getString(char *dst,Integer maxLen)
{
	strncpy(dst,m_string,maxLen);
}

Integer ParseName::expectFirstNameChar(StringParser *sp)
{
	char c=sp->getCurrentChar();

	fillExpected(sp,"a-zA-Z./_");
	
	Integer result =  isAlpha(c)||(c=='.')||(c=='/')||(c=='_');
	if(result) sp->getChar();
	return result;
}

Integer ParseName::expectNameChar(StringParser *sp)
{
	char c=sp->getCurrentChar();
	Integer result = isAlpha(c)||(c=='.')||(c=='/')||(c=='_') || isNumeric(c);
	fillExpected(sp,"a-zA-Z0-9./_");
	if(result) sp->getChar();

	//printf("expectNameChar: [%c] -> %d\n",c,result);
	return result;
}

Integer ParseName::parse(StringParser *sp)
{
	m_string[0]=sp->getCurrentChar();
	if(!expectFirstNameChar(sp)) return 0;

	Integer i=0;
	do{	i++;
		m_string[i] = sp->getCurrentChar();	
	}while(expectNameChar(sp));
		

	m_string[i]=0;

	return 1;

}
