#include "ParseAtomRadius.h"

#include "StringParser.h"
#include "ParseName.h"
#include "ParseDouble.h"

Integer ParseAtomRadius::parse(StringParser *sp)
{

ParseName parseName;
ParseDouble parseDouble;

sp->skipChars(" \t");
if(!expectStatement(sp,&parseName)) return 0;

parseName.getString(m_element,8);

sp->skipChars(" \t");
if(!expectChar(sp,':')) return 0;
sp->skipChars(" \t");

if(!expectStatement(sp,&parseDouble)) return 0;

m_sigma = parseDouble.getDouble();

return 1;

}

/*
#include <stdio.h>

main()
{
const char *str="   	C	: -0.82e+1 #carbon\n";
StringParser sp(str);

ParseAtomRadius parseAtomRadius;

int result;
result = parseAtomRadius.parse(&sp);

if(result)
{
	printf("%s : %lf\n",parseAtomRadius.m_element,parseAtomRadius.m_sigma);
}

}
*/

