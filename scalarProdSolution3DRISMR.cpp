#include "scalarProdSolution3DRISMR.h"

#include "Solution3DRISMR.h"
#include "Exception.h"
#include "Grid3DRISM.h"
#include "Settings.h"

Real 	scalarProdSolution3DRISMR(Solution *x,Solution *y)
{
Solution3DRISMR *X = dynamic_cast<Solution3DRISMR *>(x);
Solution3DRISMR *Y = dynamic_cast<Solution3DRISMR *>(y);


if(!X || !Y)
	throw new Exception(NULL,"scalarProdSolution3DRISMR : invalid class of args");

Integer N = X->getTotalSizeOfGamma();
Real *xptr = X->getRawData();
Real *yptr = Y->getRawData();

Real S=0;
while(N--) 
{
	S+= (*xptr) * (*yptr);
	xptr++;
	yptr++;
}

#if DEBUG_STRANGE_04
printf("scalarProdSolution3DRISM: %lf\n",S);


#endif

Grid3DRISM *grid = (Grid3DRISM *)X->getGrid();
Integer NSites = X->getNumberOfSites();
	
return S * grid->getDRx() * grid->getDRy() * grid->getDRz() / NSites;

}
