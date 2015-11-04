#include "getColumns.h"
#include "Settings.h"


void getColumns(Real *matrix, 
		Integer nlin,
		Integer ncol,
		Real *columnData, // out, shuld be pre-allocated of size nlin*ncol*sizeof(Real)
		Real **columns    // out, should be pre-allocated of size ncol*sizeof(Real *)
		)
{
Integer i,j,MN;
Real *src,*dst;

src = matrix;
dst = columnData;

MN = nlin*ncol;

for(i=0;i<nlin;i++,dst-= (MN-1) )
{
	for(j=0;j<ncol;j++,src++,dst+=nlin)
	{
		*dst = *src;
	}
}

for(i=0;i<ncol;i++)
	columns[i] = columnData + nlin*i;

}
