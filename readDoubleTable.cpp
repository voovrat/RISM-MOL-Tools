#include "readDoubleTable.h"

#include <stdlib.h>

#include "StringParser.h"
#include "sizeOfFile.h"
#include "countLines.h"
#include "countCols.h"

#include "ParseStringException.h"

#include "ParseDoubleTable.h"

void readDoubleTable(	const char *fname,
			Integer *nlin,	//out
			Integer *ncol,	//out
			Real **result //out, will be allocated
			)
{
	Integer N = sizeOfFile(fname);
	char *S = (char *)malloc(N+1);	
	char Error[256];

	*result=NULL;
	*nlin=0;
	*ncol=0;


	FILE *f=fopen(fname,"rb");
	if(!f)
	{	sprintf(Error,"readDoubleTable: could not open %s\n",fname);
		throw new Exception(NULL,Error);
	}




	if(N==0) 
	{
		*result=0;
		*nlin=0;
		*ncol=0;
		return;
	}

	fread(S,1,N,f);
	fclose(f);

	S[N]=0;

	StringParser sp(S);

	ParseDoubleTable parseDoubleTable;


try{
	parseDoubleTable.parse(&sp);
}catch(Exception *e)
{
	free(S);
	throw e;
}

	free(S);

	*result = parseDoubleTable.createTable();

	*nlin = parseDoubleTable.getNumberOfLines();
	*ncol = parseDoubleTable.getNumberOfColumns();

}
