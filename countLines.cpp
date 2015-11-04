#include "countLines.h"

#include "StringParser.h"

Integer countLines(char *S)
{
StringParser sp(S);

Integer NLin=0;
while(!sp.isOver())
{	NLin++;
 	sp.skipUntil("\n");
	sp.skipEOL();
}

return NLin;

}
