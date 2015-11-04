#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "parseCommandArguments.h"
#include "readGrid.h"

#include "Parameters.h"
#include "ParametersAdaptor3DRISM.h"
#include "Exception.h"

// reading functions from file
#include "readDoubleTableSimple.h"
#include "Grid3DRISM.h"
#include "Solution3DRISMR.h"

#include "readFunctionFromFile.h"
// saving results
#include "Units.h"

// for site densities, siteMultiplicities, KBT, etc
#include "MGFactoryCollection3DRISM3.h"
#include "GridIndependent3DRISM3.h"
#include "SiteMultiplicities.h"
#include "SiteDensities.h"


char paramFile[256];
char additionalParams[2048];
char Error[256];
char prefix[256];
Parameters params;
int Nx,Ny,Nz;
double dx,dy,dz;
char fname[256];


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

        MGFactoryCollection3DRISM3 *factories= new MGFactoryCollection3DRISM3();
        factories->init(&pa);

	Solution3DRISMR *g = (Solution3DRISMR *)factories->createSolution(&grid0);

	readFunctionFromFile(	prefix,	//const char *prefix,
				"g",//const char *functionName,
				g	//Solution3DRISMR *gamma //out
				);

	double K = Units::distanceUnits()->unit2unit("Bohr","Angstr");
	

	double dr = dx;
	int N = Nx < Ny ? Nx : Ny;
	    N = N < Nz ? N : Nz;

	  N/=2;

	double *Sum = (double *)malloc(N * sizeof(double) );
	double *Norm = (double *)malloc(N * sizeof(double) ); 

	memset(Sum, 0, N * sizeof(double));
	memset(Norm, 0, N * sizeof(double));

	int bin;

	int site;
	FILE *f;
	for(site=0;site<g->getNumberOfSites();site++)
	{
		GAMMA_FOR_SOLUTION(g,site)
		{
			double R = GAMMA_FOR_R;
	
			bin = (int)(R / dr + 0.5);
	
			if(bin<N) 
			{
	
				Norm[bin]++;
				Sum[bin] += GAMMA_FOR_DATA;
			}
	
		}
		END_GAMMA_FOR_SOLUTION	

				
		sprintf(fname,"%srdf%d.dat",prefix,site);
		f = fopen(fname,"w");
	
		int i;
		for(i=0;i<N;i++)
		{
			double val = Norm[i] ? Sum[i]/Norm[i] : 0;
			fprintf(f,"%10.3lf %10.3f\n",i*dr*K,val);
		}

		fclose(f);

	}


	free(Sum);
	free(Norm);

	NULL_DELETE( factories );
	NULL_DELETE( g );

	return 0;		
	 
}catch(Exception *e)
{
printf("Exception: %s\n",e->toString());
NULL_DELETE(e);
}

return 1;
}

