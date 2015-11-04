#include "loadParametersFile.h"

#include <stdio.h>
#include <stdlib.h>
#include "sizeOfFile.h"
#include "ParseParameters.h"
#include "StringParser.h"
#include "calculateLineAndCol.h"

void loadParametersFile(const char *fname,
			Parameters *parameters,
			const char *distanceUnits,
			const char *energyUnits)
{

Integer N = sizeOfFile(fname);
char Error[256];
FILE *f=fopen(fname,"r");
if(!f)
{	sprintf(Error,"could not open file %s",fname);
	throw new Exception(NULL,Error);
}

char *str = (char *)malloc(N+1);

fread(str,1,N,f);
str[N]=0;
fclose(f);


StringParser sp(str);

ParseParameters parseParameters(distanceUnits,energyUnits,parameters);

Integer line,col;

if(!parseParameters(&sp))
{	char expected[512];
	parseParameters.getExpected(expected,512);
	
	calculateLineAndCol(	str,			//const char *text,
			 	parseParameters.getErrorPos(),//const char *pos,
				&line,		//Integer *line, //out
				&col		//Integer *col   //out
			);
	char Error[512];
	sprintf(Error,"File %s: Parse error at line %d col %d: %s",fname,(int)line,(int)col,expected);

	throw new Exception(NULL,Error);

}

}
