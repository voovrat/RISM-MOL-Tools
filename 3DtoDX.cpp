#include <stdio.h>
#include <stdlib.h>

#include "Exception.h"

#include "normalizeGrid.h"

#include "Grid3DRISM.h"
#include "readGrid.h"
#include "readDoubleTableSimple.h"
#include "Units.h"
#include "ArrayOperations.h"

//#include "writeDoubleArrayToFile.h"

main(int argc,char *argv[])
{
try {

if(argc<=3)
{
	puts("Usage: 3DtoDX  gridPrefix file.3d file.dx");
	return 1;
}

const char *gridPrefix = argv[1];
const char *inputFile = argv[2];
const char *outputFile = argv[3];


Grid3DRISM grid;
readGrid(gridPrefix,	//const char *prefix,
	 &grid		//Grid3DRISM *grid
	);

Integer N = grid.getNx() * grid.getNy() * grid.getNz();

Integer nlin,ncol;
Real *input_data;

readDoubleTableSimple(	inputFile,	//const char *fname,
			&nlin,	//Integer *nlin,	//out
			&ncol,	//Integer *ncol,	//out
			&input_data	//Real **result //out, will be allocated
			);

if(N!=nlin)
	throw "Number of lines in input.3d file is inconsistent with the grid";

Real *output_data = (Real *)malloc( N * sizeof(Real) );

Real *gridPointsX = (Real *)malloc( grid.getNx() * sizeof(Real));
Real *gridPointsY = (Real *)malloc( grid.getNy() * sizeof(Real));
Real *gridPointsZ = (Real *)malloc( grid.getNz() * sizeof(Real));

normalizeGrid(	input_data,	//Real *in
		&grid,		//Grid3DRISM *grid,
		output_data,	//Real *out,
		gridPointsX,	//Real *gridPointsX = NULL, // grid 
		gridPointsY,	//Real *gridPointsY = NULL,
		gridPointsZ	//Real *gridPointsZ = NULL
		);

Real kAngstr = Units::distanceUnits()->unit2unit("Bohr","Angstr");

mulArrayScalar<Real,Real>(gridPointsX,kAngstr,grid.getNx());
mulArrayScalar<Real,Real>(gridPointsY,kAngstr,grid.getNy());
mulArrayScalar<Real,Real>(gridPointsZ,kAngstr,grid.getNz());



FILE *f=fopen(outputFile,"w");

Integer Nx=grid.getNx();
Integer Ny=grid.getNy();
Integer Nz=grid.getNz();

fprintf(f,"object 1 class gridpositions counts%8ld%8ld%8ld\n",Nx,Ny,Nz);
fprintf(f,"origin%16lg%16lg%16lg\n",gridPointsX[0],gridPointsY[0],gridPointsZ[0]);
fprintf(f,"delta %16lg 0 0\n",gridPointsX[1] - gridPointsX[0]);
fprintf(f,"delta 0 %16lg 0\n",gridPointsY[1] - gridPointsY[0]);
fprintf(f,"delta 0 0 %16lg\n",gridPointsZ[1] - gridPointsZ[0]);
fprintf(f,"object 2 class gridconnections counts%8ld%8ld%8ld\n",Nx,Ny,Nz);
fprintf(f,"object 3 class array type double rank 0 items%8ld follows\n",Nx*Ny*Nz);

int col=1;

int i,j,k;
Real *pout = output_data;
for(j=0;j<Nx;j++)
{
    printf("%6.2lg%% done\n",(Real)j/Nx*100);
    for(i=0;i<Ny;i++)
    {   for(k=0;k<Nz;k++)
	{
   
		fprintf(f,"%16lE",*pout);
		col=col+1;
		if(col>3)
		{
		    fprintf(f,"\n");
		    col=1;
		}
		pout++;
        }//k
    }//i
}//j
if(col!=1) fprintf(f,"\n");
fprintf(f,"object \"Untitled\" call field\n");
fclose(f);

free(gridPointsX);
free(gridPointsY);
free(gridPointsZ);
free(output_data);
free(input_data);

} catch( Exception *e ) {
	printf("Exception: %s\n",e->toString());
} catch( const char *str ) {
	printf("Exception: %s\n",str);
}
return 0;

}
