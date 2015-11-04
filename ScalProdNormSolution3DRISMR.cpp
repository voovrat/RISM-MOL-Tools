#include "ScalProdNormSolution3DRISMR.h"

#include "Solution3DRISMR.h"
#include "scalarProdSolution3DRISMR.h"

#include "Exception.h"

#include "TextLog.h"


Real ScalProdNormSolution3DRISMR::calculateNorm(Object *x,Object *y)
{
	Solution3DRISMR *X = dynamic_cast<Solution3DRISMR *>(x);
	Solution3DRISMR *Y = dynamic_cast<Solution3DRISMR *>(y);

	if(!X || !Y) 
	 	throw new Exception(this,"ScalProdNormSolution3DRISMR::calculateNorm : incorect class of args");

	//TextLog *log = TextLog::getInstance();
	


	SolutionFactory3DRISMR solutionFactory(	X->getNumberOfSites());

	Solution3DRISMR *tmp = (Solution3DRISMR *) solutionFactory.createSolution(X->getGrid());

	X->copy(tmp);
	subSolution3DRISMR(tmp,Y);
	
	Real r = scalarProdSolution3DRISMR(tmp,tmp);	char s[256];

#if VERBOSE_SCAL_PROD_NORM
	printf("Norm=%le\n",r);
#endif	
	
	//Grid3DRISM *g3d = (Grid3DRISM*)X->getGrid();
	//sprintf(s,"gird: %dx%dx%d  :  norm:%le",g3d->getNx(),g3d->getNy(),g3d->getNz(),r);
	//log->printString(2,s);

	NULL_DELETE(tmp);
	return r;
}
