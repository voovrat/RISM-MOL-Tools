#include "ParseInteger.h"

#include <stdlib.h>
#include "StringParser.h"
#include "ParseUnsigned.h"

Integer ParseInteger::parse(StringParser *sp)
{
	
	ParseUnsigned uInteger;

	m_sign = 1;

	if(expectStatement(sp,&uInteger)) 
	{
		m_integer = uInteger.getInteger();
		return 1;
	}	
	
	char c  = sp->getCurrentChar();
	
	if(!expectChars(sp,"+-")) return 0;

	m_sign = (c=='+') ? 1 : -1; 

	if(!expectStatement(sp,&uInteger)) return 0;

	m_integer = m_sign*uInteger.getInteger();

	return 1;	

}
