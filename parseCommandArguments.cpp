#include "parseCommandArguments.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Parsing parameters
#include "ParseParameters.h"
#include "sizeOfFile.h"
#include "Exception.h"
#include "StringParser.h"

// reading functions from file
//#include "readDoubleTableSimple.h"
//#include "Grid3DRISM.h"
//#include "Solution3DRISMR.h"

// for site densities, siteMultiplicities, KBT, etc
//#include "MGFactoryCollection3DRISM3.h"
//#include "GridIndependent3DRISM3.h"
//#include "SiteMultiplicities.h"
//#include "SiteDensities.h"


	
void parseCommandArguments(
int argc,  // in
char *argv[],   //in
Parameters *params, //in/out
char *paramFile, //out
char *additionalParams, //out
char *Error, // aux
char *prefix //out
)
{
	additionalParams[0]=0;

	if(argc<2)
	{
		puts("Usage: ./calculateFreeEnergy prefix [parameters.txt] [Additional parameters string]");
		puts("For proper work of the program one shoud have the following files:");
		puts("\t- ${prefix}gamma${site}.3d");
		puts("\t- ${prefix}c${site}.3d");
		puts("\t- ${prefix}clong${site}.3d");
		puts("\t- ${prefix}X.grd");
		puts("\t- ${prefix}Y.grd");
		puts("\t- ${prefix}Z.grd");
		puts("If no parameters file is given, the file ${prefix}_parameters.txt is used");

		throw new Exception(NULL,"incorrect command line arguments");
		return;
	}

	strcpy(prefix,argv[1]);

	if(argc>2)
		strcpy(paramFile,argv[2]);
	else
		sprintf(paramFile,"%sparameters.txt",prefix);

	if(argc>3)
	{
		strcpy(additionalParams,argv[3]);
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
					params		//Parameters *parameters
					);

	parseParameters.parse(&spFile);


	free(str);	

	StringParser spArg(additionalParams);

	parseParameters.parse(&spArg);

}


