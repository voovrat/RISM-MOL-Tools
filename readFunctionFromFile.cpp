#include "readFunctionFromFile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Solution3DRISMR.h"
#include "readDoubleTableSimple.h"
#include "Exception.h"

void readFunctionFromFile(	const char *prefix,
				const char *functionName,
				Solution3DRISMR *gamma //out
			)
{
static char Error[512];
char str[256];
double *data;
int site;
int Nsite = gamma->getNumberOfSites();
Integer nrow,ncol;


for(site=0;site<Nsite;site++)
{
	sprintf(str,"%s%s%d.3d",prefix,functionName,site);
	readDoubleTableSimple(str,	//const char *fname,
		&nrow,	//Integer *Nrow,  //out
		&ncol,	//Integer *Ncol,  //out
		&data//Real **result //out, will be allocated
		);

	if(ncol != 1 || nrow != gamma->getSizeOfOneGamma())
	{
		sprintf(Error,"invalid data in input %s file: nrow=%ld, ncol=%ld, sizeOfGamma=%ld",
				functionName,
				nrow,
				ncol,
				(Integer)gamma->getSizeOfOneGamma()
		);	
		throw new Exception(NULL,Error);	
	}

	memcpy(gamma->getGamma()[site],data,gamma->getSizeOfOneGamma() * sizeof(double) );

	free(data);
}

}
