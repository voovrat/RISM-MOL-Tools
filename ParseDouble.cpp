#include "ParseDouble.h"

#include <math.h>
#include "StringParser.h"
#include "ParseNumberWithPoint.h"
#include "ParseInteger.h"


Integer ParseDouble::parse(StringParser *sp)
{
	ParseNumberWithPoint numberWithPoint;
	ParseInteger parseInteger;

	if(!expectStatement(sp,&numberWithPoint)) return 0;

	m_value = numberWithPoint.getDouble();

	if(!expectChars(sp,"eE")) return 1;

	if(!expectStatement(sp,&parseInteger)) return 0;

	Integer exponent = (Integer)parseInteger.getInteger();

	m_value *= pow((double)10,(int)exponent);

	return 1;

}
