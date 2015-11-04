#include "readGrids.h"

#include <stdlib.h>
#include <stdio.h>

#include "readDoubleTableSimple.h"


void readGrids(const char *prefix, int *Nx,int *Ny,int *Nz,double *dx,double *dy,double *dz)
{
	
	char str[256];
	double *data;
	Integer nrow,ncol;
	
	sprintf(str,"%sX.grd",prefix);
	readDoubleTableSimple(str,	//const char *fname,
	                &nrow,	//Integer *Nrow,  //out
	                &ncol,	//Integer *Ncol,  //out
	                &data//Real **result //out, will be allocated
	                );
	*Nx = nrow;
	*dx = data[1]-data[0];
	free(data);
	
	sprintf(str,"%sY.grd",prefix);
	readDoubleTableSimple(str,	//const char *fname,
	                &nrow,	//Integer *Nrow,  //out
	                &ncol,	//Integer *Ncol,  //out
	                &data//Real **result //out, will be allocated
	                );
	*Ny = nrow;
	*dy = data[1]-data[0];
	free(data);
	
	sprintf(str,"%sZ.grd",prefix);
	readDoubleTableSimple(str,	//const char *fname,
	                &nrow,	//Integer *Nrow,  //out
	                &ncol,	//Integer *Ncol,  //out
	                &data//Real **result //out, will be allocated
	                );
	*Nz = nrow;
	*dz = data[1]-data[0];
	free(data);
}

