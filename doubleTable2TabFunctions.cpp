#include "doubleTable2TabFunctions.h"

#include "TabFunction.h"
#include "getColumns.h"
#include <string.h>
#include "Pointer.h"


// First column - r-vector, other columns - data
//
void doubleTable2TabFunctions( 
			Real *data,			// line-by-line Real data
			Integer nlin,
			Integer ncol,
			TabFunction **tabFunctions,	//out, should be preallocated (ncol-1)
			Real unitKoef
		)
{
	Integer i;

	Real *cdata = (Real *)malloc(nlin*ncol*sizeof(Real));
	Real **cols = (Real **)malloc(ncol*sizeof(Real *));

	getColumns(	data,	//Real *matrix, 
			nlin,	//Integer nlin,
			ncol,	//Integer ncol,
			cdata,	//Real *columnData, // out
			cols	//		Real **columns    // out
		);


	Real x0 = cols[0][0] * unitKoef;
	Real dx = (cols[0][1]-x0)*unitKoef;

	for(i=0;i<ncol-1;i++)
	{	
		Real *fnvals = (Real *)malloc(nlin * sizeof(Real) );
		memcpy(fnvals,cols[i+1],nlin*sizeof(Real));
		tabFunctions[i]->init(fnvals,nlin,x0,dx);
		tabFunctions[i]->addToDeleteList(new Pointer(fnvals));
	}

	free(cdata);
	free(cols);
}
