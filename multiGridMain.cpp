#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ParseParameters.h"
#include "ParametersAdaptor3DRISM.h"
#include "MultiGridInterface.h"
#include "sizeOfFile.h"
#include "Exception.h"
#include "saveResults3DRISM.h"
#include "Parameters.h"
#include "StringParser.h"

main(int argc,char *argv[])
{
	char paramFile[256];
	char additionalParams[2048];
	char Error[256];
	Parameters params;
	

	if(argc<2)
	{
		puts("Usage: ./multiGridMain <parametersFile.txt> [ <optional parameters string>]");
		return 0;
	}


try{


	strcpy(paramFile,argv[1]);
	
	if(argc>2)
	{
		strcpy(additionalParams,argv[2]);
	}

	Integer L=sizeOfFile(paramFile);

	FILE *f=fopen(paramFile,"r");

	if(L==0 || f==NULL)
	{	
		sprintf(Error,"Cannot read parameters form file %s",paramFile);	
		throw new Exception(NULL,Error);
	}

	char *str = (char*)malloc(L+1);
	fread(str,1,L,f);
	fclose(f);


	StringParser spFile(str);

	ParseParameters parseParameters("Bohr",		//const char *distanceUnits,
					"Hartree",	//const char * energyUnits,
					&params		//Parameters *parameters
					);

	parseParameters.parse(&spFile);


	free(str);	

	StringParser spArg(additionalParams);

	parseParameters.parse(&spArg);


	puts(params.toString());
	
	ParametersAdaptor3DRISM parametersAdaptor(&params);

	MultiGridInterface mgi(&parametersAdaptor);

	mgi.init();
	mgi.solve();
	mgi.saveResults();
	//mgi.saveFreeEnergies();

//	saveResults3DRISM(
//			mgi.getGamma(),	//Solution3DRISMR *gamma,
//			mgi.getC(),	//Solution3DRISMR *c,
//			mgi.getG(),	//Solution3DRISMR *g,
//			"",	//const char *prefix,
//			".3d"	//const char *suffix
//		);
		
	

	 
}catch(Exception *e)
{
printf("Exception: %s\n",e->toString());
delete e;
}
catch(const char *s)
{
	printf("char exception %s\n",s);
}

}

