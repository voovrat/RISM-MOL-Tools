#include "readTabFunctionFromFile.h"

#include "TabFunction.h"

#include "readDoubleTable.h"
#include "getColumns.h"

#include <string.h>

#include "Pointer.h"

#include "Exception.h"

void readTabFunctionFromFile(const char *fname, TabFunction *fn)
{
	Real *data;
	Integer nlin,ncol;

	readDoubleTable(fname,	//	const char *fname,
			&nlin,	//Integer *Nrow,	//out
			&ncol,	//Integer *Ncol,	//out
			&data 	//Real **result //out, will be allocated
			);

	Real *cdata = (Real *)malloc(nlin*ncol*sizeof(Real));
	Real **cols = (Real **)malloc(ncol*sizeof(Real *));

	getColumns(	data,	//Real *matrix, 
			nlin,	//Integer nlin,
			ncol,	//Integer ncol,
			cdata,	//Real *columnData, // out, shuld be pre-allocated of size nlin*ncol*sizeof(Real)
			cols	//		Real **columns    // out, should be pre-allocated of size ncol*sizeof(Real *)
		);
		

	free(data);
	
	if(ncol!=2)
	{
		free(cdata);		

		throw new Exception(NULL,"readTabFunctionFromFile : number of columns should be 2!!");
	}

	Real x0 = cols[0][0];
	Real dx = cols[0][1]-x0;

	Real *fnvals = (Real *)malloc(nlin * sizeof(Real));

	memcpy(fnvals,cols[1],nlin*sizeof(Real));

	free(cdata);
	free(cols);

	fn->init(fnvals,nlin,x0,dx);
	fn->addToDeleteList(new Pointer(fnvals));

}
