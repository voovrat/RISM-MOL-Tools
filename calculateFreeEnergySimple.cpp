#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Parsing parameters
#include "ParseParameters.h"
#include "ParametersAdaptor3DRISM.h"
#include "sizeOfFile.h"
#include "Exception.h"
#include "StringParser.h"

#include "parseCommandArguments.h"


#include "readGrid.h"

// reading functions from file
#include "readDoubleTableSimple.h"
#include "Grid3DRISM.h"
#include "Solution3DRISMR.h"

#include "readFunctionFromFile.h"

// for site densities, siteMultiplicities, KBT, etc
#include "MGFactoryCollection3DRISM3.h"
#include "GridIndependent3DRISM3.h"
#include "SiteMultiplicities.h"
#include "SiteDensities.h"

// calculating Free Energy and PMV
#include "calculateHNCFreeEnergy.h"
#include "calculateKHFreeEnergy.h"
#include "calculateGFFreeEnergy.h"
#include "calculateExcludedVolume.h"
#include "calculateMyHNCFreeEnergy.h"

// saving results
#include "Units.h"


char paramFile[256];
char additionalParams[2048];
char Error[256];
char prefix[256];
Parameters params;
int Nx,Ny,Nz;
double dx,dy,dz;


main(int argc,char *argv[])
{

try{
	parseCommandArguments(
		argc,  // in
		argv,   //in
		&params, //in/out
		paramFile, //out
		additionalParams, //out
		Error, // aux
		prefix //out
	);
	
	printf("prefix = [%s]\n",prefix);
	printf("Parameters =  [%s]\n", paramFile);
	printf("AdditionalParameters = [%s]\n",additionalParams);

	ParametersAdaptor3DRISM pa(&params);

	char Error[256];

        MGFactoryCollection3DRISM3 *factories= new MGFactoryCollection3DRISM3();
        factories->init(&pa);

	GridIndependent3DRISM3 *gridIndependent = (GridIndependent3DRISM3 *) factories->m_gridIndependent;

	Grid3DRISM grid0(1,1,1,1,1,1);

	char prefix0[256];
	strcpy(prefix0,prefix);
	prefix0[strlen(prefix)-1]=0;

	readGrid(prefix0,&grid0);	

	Nx = grid0.getNx();
	Ny = grid0.getNy();
	Nz = grid0.getNz();

	dx = grid0.getDRx();
	dy = grid0.getDRy();
	dz = grid0.getDRz();


	printf("SIZES  =%d x %d x %d \n",Nx,Ny,Nz);
	printf("SPACING = %lf ,%lf, %lf \n",dx,dy,dz);

//	Grid3DRISM grid0(Nx,Ny,Nz,dx,dy,dz);


	Solution3DRISMR *gamma = (Solution3DRISMR *)factories->createSolution(&grid0);
	Solution3DRISMR *c = (Solution3DRISMR *)factories->createSolution(&grid0);
	Solution3DRISMR *clong= (Solution3DRISMR *)factories->createSolution(&grid0);
	Solution3DRISMR *ctotal = (Solution3DRISMR *)factories->createSolution(&grid0);



	readFunctionFromFile(	prefix,	//const char *prefix,
				"gamma",//const char *functionName,
				gamma	//Solution3DRISMR *gamma //out
				);
	
	readFunctionFromFile(	prefix,	//const char *prefix,
				"c",	//const char *functionName,
				c	//Solution3DRISMR *gamma //out
				);
	
	readFunctionFromFile(	prefix,	//const char *prefix,
				"clong",//const char *functionName,
				clong	//Solution3DRISMR *gamma //out
				);

	c->copy(ctotal); // ctotal = c
	addSolution3DRISMR(ctotal,clong); //ctotal +=clong

	double value_KH= calculateKHFreeEnergy(
				gamma,		//Solution3DRISMR *gamma,				
				c,		//Solution3DRISMR *c,				
				clong,		//Solution3DRISMR *minusBetaUlong,
				gridIndependent->getKBT(),			//Real kBT,
				gridIndependent->getSiteDensities()->getDensity(),//Real *densities,
				gridIndependent->getSiteMultiplicities()->getSiteMultiplicities()	//Integer *multiplicities
			 );	

	double value_GF= calculateGFFreeEnergy(
				gamma,		//Solution3DRISMR *gamma,				
				c,		//Solution3DRISMR *c,				
				clong,		//Solution3DRISMR *minusBetaUlong,
				gridIndependent->getKBT(),			//Real kBT,
				gridIndependent->getSiteDensities()->getDensity(),//Real *densities,
				gridIndependent->getSiteMultiplicities()->getSiteMultiplicities()	//Integer *multiplicities
			 	);


	double value_HNC = calculateHNCFreeEnergy(
				gamma,		//Solution3DRISMR *gamma,				
				c,		//Solution3DRISMR *c,				
				clong,		//Solution3DRISMR *minusBetaUlong,
				gridIndependent->getKBT(),			//Real kBT,
				gridIndependent->getSiteDensities()->getDensity(),//Real *densities,
				gridIndependent->getSiteMultiplicities()->getSiteMultiplicities()	//Integer *multiplicities
			 	);

	double excludedVolume = 
			calculateExcludedVolume( 
				gridIndependent->getSolventRDFs(),	//TabFunction **solventRDFs, 
				gamma,		//Solution3DRISMR *gamma,	
				ctotal,		//Solution3DRISMR *c,
				gridIndependent->getSiteDensities()->getDensity(),//Real *densities,  
				gridIndependent->getSiteMultiplicities()->getSiteMultiplicities()//	Integer *multiplicities
			 	);


	double value_MyHNC = calculateMyHNCFreeEnergy(
				gamma,		//Solution3DRISMR *gamma,
				c,		//Solution3DRISMR *c,				
				clong,		//Solution3DRISMR *minusBetaUlong,
				gridIndependent->getKBT(),			//Real kBT,
				gridIndependent->getSiteDensities()->getDensity(),//Real *densities,
				gridIndependent->getSiteMultiplicities()->getSiteMultiplicities()	//Integer *multiplicities
			 	);
	double B2A = Units::distanceUnits()->unit2unit("Bohr","Angstr");
	double B2A3 = B2A*B2A*B2A;

	printf("HNC: %lf [kcal/mol]\n",value_HNC*Units::energyUnits()->unit2unit("Hartree","kcal/mol"));
	printf("KH: %lf [kcal/mol]\n",value_KH*Units::energyUnits()->unit2unit("Hartree","kcal/mol"));
	printf("GF: %lf [kcal/mol]\n",value_GF*Units::energyUnits()->unit2unit("Hartree","kcal/mol"));
	printf("VUA: %lf [Angstr^3]\n", excludedVolume * B2A3 );
//	printf("SVP: %lf [kcal/mol]\n",value_MyHNC*Units::energyUnits()->unit2unit("Hartree","kcal/mol"));
	


	NULL_DELETE( gamma );
	NULL_DELETE( c );
	NULL_DELETE( clong );
	NULL_DELETE( ctotal );
	NULL_DELETE( factories);
	
	return 0;		
	 
}catch(Exception *e)
{
printf("Exception: %s\n",e->toString());
NULL_DELETE(e);
}

return 1;
}

