#include <stdio.h>
#include <stdlib.h>

#include "Grid3DRISM.h"
#include "readDoubleTableSimple.h"

void readGrid(	const char *prefix,
		Grid3DRISM *grid)
{
Real *data;
Integer nlin,ncol;

Real dx,dy,dz;
Integer Nx,Ny,Nz;

char fname[256];

sprintf(fname,"%s_X.grd",prefix);
readDoubleTableSimple(	fname,	//const char *fname,
			&nlin,	//Integer *nlin,	//out
			&ncol,	//Integer *ncol,	//out
			&data	//Real **result //out, will be allocated
			);
dx = data[1]-data[0];
Nx = nlin;
free(data);

sprintf(fname,"%s_Y.grd",prefix);
readDoubleTableSimple(	fname,	//const char *fname,
			&nlin,	//Integer *nlin,	//out
			&ncol,	//Integer *ncol,	//out
			&data	//Real **result //out, will be allocated
			);
dy = data[1]-data[0];
Ny = nlin;
free(data);

sprintf(fname,"%s_Z.grd",prefix);
readDoubleTableSimple(	fname,	//const char *fname,
			&nlin,	//Integer *nlin,	//out
			&ncol,	//Integer *ncol,	//out
			&data	//Real **result //out, will be allocated
			);
dz = data[1]-data[0];
Nz = nlin;
free(data);

Grid3DRISM grd0(Nx,Ny,Nz,dx,dy,dz);

grd0.copy(grid);

}
