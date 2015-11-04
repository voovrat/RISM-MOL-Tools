#include "L2Norm3DRISM.h"

#include "Solution3DRISMR.h"
#include "Closure3DRISM.h"
#include "Exception.h"
#include "GridDependentInterface3DRISM.h"

#include <math.h>

Real L2Norm3DRISM::calculateNorm(Object *x,Object *y)
{
	Solution3DRISMR *X = dynamic_cast<Solution3DRISMR*>(x);
	Solution3DRISMR *Y = dynamic_cast<Solution3DRISMR*>(y);

	if(!X || !Y)
		throw new Exception(this,"L2Norm3DRISM::calculateNorm : invalid class  ");

	Integer numSites = X->getNumberOfSites();
	Integer site;

	Grid3DRISM *grid = (Grid3DRISM*)X->getGrid();
	
	Real dx = grid->getDRx();
	Real dy = grid->getDRy();
	Real dz = grid->getDRz();
	
	Real norm=0;
	for(site = 0; site<numSites; site++)
	{
		Real *x_ptr = X->getGamma()[site];
		Real *y_ptr = Y->getGamma()[site];
		Integer N = X->getSizeOfOneGamma();


		Real S=0;
		while(N--)
		{
			Real df = (*x_ptr - *y_ptr);
			S+= df*df;
		}
		norm += sqrt(S*dx*dy*dz);
	
	}

	norm /= numSites;

	return norm;
}

Norm *L2Norm3DRISMFactory::createNorm(GridDependentData *gridDependent)
{
	GridDependentInterface3DRISM *gridDependent3D =
		dynamic_cast<GridDependentInterface3DRISM*>(gridDependent);

	if(!gridDependent3D)
		throw new Exception(this,"L2Norm3DRISMFactory::createNorm : invalid argument class");
	
	return new L2Norm3DRISM(gridDependent3D->getClosure(), //	Closure3DRISM *closure,
		m_solutionFactory //SolutionFactory3DRISMR *solutionFactory
		);
}
