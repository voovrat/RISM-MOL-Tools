#include "countCols.h"

#include "StringParser.h"
#include "ParseStringException.h"

Integer countCols(char *S)
{
StringParser sp(S);

sp.skipSpace();

Integer ncol=0;
while(!sp.currentCharIs("\n\r"))
{	
	sp.skipChars(" \t");
	sp.getDouble();
	if(sp.getError()) 
		throw new ParseStringException(NULL,(char *)"countCols : expected Real");
	sp.skipChars(" \t");
	ncol++;
}
return ncol;
}
