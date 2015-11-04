#include "Settings.h"
#include "Grid3DRISM.h"

#include "conv3D.h"
#include "ArrayOperations.h"

#include <stdlib.h>

// calculates regions

void findProbableGmaxRegions(	Real **g_index, // array of g functions
				Grid3DRISM *grid,
				Integer Nsites,	// number of g functions
				Real treshold,	
				Real radius,	// radius of the filter (typically: max distance between the molecule's atoms )
				Integer *probableGmax //out (is not allocated)
				)	
{
Integer N = grid->getNx() * grid->getNy() * grid->getNz(); 

Real *F = (Real *)malloc( N * sizeof(Real) );
Real *A = (Real *)malloc( N * sizeof(Real) ); // g>treshold
Real *FA = (Real *)malloc( N * sizeof(Real) );

Real R2 = radius*radius;
Real x,y,z;
Real *pF = F;
GAMMA_FOR(grid)
{
	x = GAMMA_FOR_X;
	y = GAMMA_FOR_Y;
	z = GAMMA_FOR_Z;

	*pF = (x*x + y*y + z*z < R2 );
	
	pF++;
}
END_GAMMA_FOR

setArrayScalar<Integer,Integer>(probableGmax,	//DataType *dst,
				0,		//ScalarType scalar,
				N		//Integer N
			);




Integer site;
for(site = 0; site<Nsites; site++)
{

	int i;
	Real *pA,*pg;
	for(i=0, pA=A, pg = g_index[site]; 
		i<N; 
		i++,pA++,pg++)
	{
		*pA = (*pg > treshold );
	}


	conv3D(	A,	//Real *A,
		F,	//Real *B,
		grid,	//Grid3DRISM *grid,
		FA	//Real *C // out: C=conv(A,B)
		);

	
	Real *pFA;
	Integer *pR;
	for(	i=0, pFA = FA, pR = probableGmax;
		i<N;
		i++, pFA++, pR++)
	{
		if(*pFA>0.5) *pR = 1;
	}

}//for

free(FA);
free(A);
free(F);
}

/*
#include "readGrid.h"
#include <stdio.h>
#include <stdlib.h>
#include "readDoubleTableSimple.h"
#include "Exception.h"
#include "writeDoubleArrayToFile.h"
#include "getMaxDistance.h"

main()
{
Real TRESHOLD = 2;

try{
Grid3DRISM grid;

const char *prefix = "CD_in_NaClRISM";

readGrid(	prefix,	//const char *prefix,
		&grid	//Grid3DRISM *grid
	);

Integer N = grid.getNx() * grid.getNy() * grid.getNz();

Integer nlin,ncol;
Real *g0,*g1;

char fname[256];
sprintf(fname,"%s_g0.3d",prefix);

readDoubleTableSimple(	fname,	//const char *fname,
			&nlin,	//Integer *nlin,	//out
			&ncol,	//Integer *ncol,	//out
			&g0	//Real **result //out, will be allocated
			);

if( nlin != N)
	throw "Nnumber of samples in the first 3d file is inconsistent with grid";


readDoubleTableSimple(	fname,	//const char *fname,
			&nlin,	//Integer *nlin,	//out
			&ncol,	//Integer *ncol,	//out
			&g1	//Real **result //out, will be allocated
			);
if( nlin != N)
	throw "Nnumber of samples in the second 3d file is inconsistent with grid";

Real *g_index[3];
g_index[0] = g0;
g_index[1] = g1;
g_index[2] = g1;

Real *coors;

readDoubleTableSimple( "water.XYZ",
			&nlin,
			&ncol,
			&coors);

if(nlin!=3)
	throw "incorect number of lines in water.XYZ file";
	
Real R = getMaxDistance(coors,3) / 0.52;
				

Real *probableGmax = (Real *)malloc( N * sizeof(Real) );
	
findProbableGmaxRegions(g_index,	//Real **g_index, // array of g functions
			&grid,	//Grid3DRISM *grid,
			3,	//int Nsites,	// number of g functions
			TRESHOLD,	//Real treshold,	
			R,		//Real radius,	// radius of the filter (typically: max distance between the molecule's atoms )
			probableGmax	//Real *probableGmax //out (is not allocated)i
			);	

writeDoubleArrayToFile("P.3d",probableGmax,N);


free(probableGmax);

free(coors);
free(g0);
free(g1);

} catch (Exception *e) {
	puts(e->toString());
} catch (const char *str) {
	puts(str);
}


return 0;

}
*/
