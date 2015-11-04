#include <stdlib.h>

#include "Grid3DRISM.h"
#include "generateGridPermutation.h"


//re-arrange the elements in "in" to have the descending grid 
// ( from -N/2+1 ... N/2 in each dimension )
void normalizeGrid(	Real *in,
			Grid3DRISM *grid,
			Real *out,
			Real *gridPointsX, //=NULL
			Real *gridPointsY, //=NULL
			Real *gridPointsZ  //=NULL
		)
{

Integer NX = grid->getNx();
Integer NY = grid->getNy();
Integer NZ = grid->getNz();

Integer *PX = (Integer *)malloc( NX * sizeof(Integer) );
Integer *PY = (Integer *)malloc( NY * sizeof(Integer) );
Integer *PZ = (Integer *)malloc( NZ * sizeof(Integer) );

generateGridPermutation(NX,	//Integer N,
			PX	//Integer *P
			);

generateGridPermutation(NY,	//Integer N,
			PY	//Integer *P
			);

generateGridPermutation(NZ,	//Integer N,
			PZ	//Integer *P
			);

Real *pout = out;
Integer x_id,y_id,z_id;
Integer px_id,py_id,pz_id;

for(x_id=0; x_id<NX; x_id++)
{
	px_id = PX[x_id];
	for(y_id = 0; y_id<NY; y_id++)
	{
		py_id = PY[y_id];
		for(z_id=0; z_id<NZ; z_id++)
		{
			pz_id=PZ[z_id];

			*pout = in[pz_id + NZ*( py_id + NY*px_id  ) ];
			pout++;
		}//z_id
	}//y_id
}//x_id

Real dX = grid->getDRx();
Real dY = grid->getDRy();
Real dZ = grid->getDRz();



int i;

#define FILL_GRID_POINTS(D)	\
if(gridPoints##D ) \
{	Real d0 = (-N##D/2 + 1)*d##D; \
	for(i=0;i<N##D;i++)	gridPoints##D[i] = d0 + i * d##D;\
}

FILL_GRID_POINTS(X)
FILL_GRID_POINTS(Y)
FILL_GRID_POINTS(Z)


free(PX);
free(PY);
free(PZ);

}
