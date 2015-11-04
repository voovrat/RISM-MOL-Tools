#include "ParseNumberWithPoint.h"

#include "StringParser.h"
#include "ParseInteger.h"
#include "ParseUnsigned.h"


Integer ParseNumberWithPoint::parse(StringParser *sp)
{
	ParseInteger integer;
	ParseUnsigned uInteger;

	if(!expectStatement(sp,&integer)) return 0;

	m_value = integer.getInteger();

	if(sp->getCurrentChar()!='.') return 1;

	expectChar(sp,'.');

	Real zFrac=1;

	while(expectChar(sp,'0')) zFrac/=10;

	if(!expectStatement(sp,&uInteger)) 
	{
		if(zFrac==1) 	 return 0;
		else return 1;
	}

	Real frac = uInteger.getInteger();

	while(frac>=1) frac/=10;

	Integer sign = integer.getSign();

	m_value += frac*sign*zFrac;

	return 1;

}
