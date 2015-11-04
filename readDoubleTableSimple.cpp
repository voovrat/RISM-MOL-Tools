#include "readDoubleTableSimple.h"

#include <stdlib.h>

#include "StringParser.h"
#include "sizeOfFile.h"
#include "countLines.h"
#include "countCols.h"

#include "ParseStringException.h"

void readDoubleTableSimple(	const char *fname,
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

try{



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

	*nlin = countLines(S);
	if(*nlin==0)
		return;		
	*ncol = countCols(S);
		
	

	*result = (Real *)malloc(*nlin*(*ncol)*sizeof(Real));

	StringParser sp(S);
	
	Real *ptr = *result;
	Integer i,j;

	for(i=0;i<*nlin;i++)
	{
		sp.skipChars(" \t");

		for(j=0;j<*ncol;j++,ptr++)
		{
			*ptr = sp.getDouble();
			if(sp.getError())
			{			
				sprintf(Error,"readDoubleTable: expected Real line %d value %d",(int)i,(int)j);

				throw new ParseStringException(NULL,Error);
			}
			sp.skipChars(" \t");
	
		} //for j


		if(!sp.isOver() && !sp.currentCharIs("\n\r"))
		{
			sprintf(Error,"readDoubleTable: line %d : expected EOL",(int)i);
			throw new ParseStringException(NULL,Error);
		}
	
		sp.skipEOL();
		
	}//for i

	free(S);

}catch(ParseStringException *e)
{
	free(S);
	free(*result);
	*result= NULL;
	*nlin = *ncol = 0;
	throw e;
}



}
