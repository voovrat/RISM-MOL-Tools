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

//#include "readFunctionFromFile.h"

// for site densities, siteMultiplicities, KBT, etc
#include "MGFactoryCollection3DRISM3.h"
#include "GridIndependent3DRISM3.h"
#include "GridDependent3DRISM3.h"
#include "SiteMultiplicities.h"
#include "SiteDensities.h"

#include "generateGrid3DRISM.h"
#include "saveGrid3DRISM.h"
#include "MoleculeCharges.h"

#include "writeDoubleArrayToFile.h"

// saving results
#include "Units.h"

#include "MoleculeCoordinates.h"

char paramFile[256];
char fname[256];
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


	generateGrid3DRISM(gridIndependent->getSoluteCoordinates(), //CMoleculeCoordinates *coors,
			pa.getBuffer(), // Real buffer,
			pa.getSpacing(), //Real dr,	
			&grid0,  //Grid3DRISM *result, //out
			2 //Integer  align
			);

	int Nsites = gridIndependent->getSolventCharges()->getNumSites();


	GridDependent3DRISM3 *gridDependent = (GridDependent3DRISM3*)gridIndependent->createGridDependent(&grid0);

	Solution3DRISMR *pot = gridDependent->getBetaUshort();

	saveGrid3DRISM(	&grid0,   //Grid3DRISM *grid,
			prefix,       //const char *fileNamePrefix,
			".grd"   //const char *fileNameSuffix)
 		       );

	for(int i=0;i<Nsites;i++)	
        {
		sprintf(fname,"%spot%d.3d",prefix,i);
		writeDoubleArrayToFile(fname,//const char *fname,
				       pot->getGamma()[i],//potentReal *x,
				pot->getSizeOfOneGamma() //	Integer N
				);
	}


	NULL_DELETE(pot);
	NULL_DELETE( factories);
	
	return 0;		
	 
}catch(Exception *e)
{
printf("Exception: %s\n",e->toString());
NULL_DELETE(e);
}

return 1;
}

