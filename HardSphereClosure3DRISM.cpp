#include "HardSphereClosure3DRISM.h"

//#include "calculateBeta.h"
#include "Solution3DRISMR.h"
#include "MoleculeCoordinates.h"
#include "Closure3DRISM.h"
#include "Exception.h"
#include <stdlib.h>
#include "Units.h"
#include "readDoubleTable.h"
#include "GridIndependentInterface3DRISM.h"

HardSphereClosure3DRISM::HardSphereClosure3DRISM(
				 Real *radii ,
				 Closure3DRISM *subClosure,
				 MoleculeCoordinates *soluteCoordinates )		
{
	m_radii = radii;
	m_subClosure = subClosure;
	m_soluteCoordinates = soluteCoordinates;
}

void HardSphereClosure3DRISM::calculateClosure(Solution3DRISMR *gamma,
					Solution3DRISMR *c //out
					)
{
	m_subClosure->calculateClosure(gamma,c);

	Grid3DRISM *grid = (Grid3DRISM*)gamma->getGrid();
	Integer Nsolvent = gamma->getNumberOfSites();		
	Integer Nsolute = m_soluteCoordinates->getNumSites();

	Integer soluteSite,solventSite;

	for(solventSite = 0; solventSite<Nsolvent; solventSite++)
	{
		Real *c_ptr = c->getGamma()[solventSite];
		Real *gamma_ptr = gamma->getGamma()[solventSite];

		GAMMA_FOR(grid)
		{
			Real x = GAMMA_FOR_X;
			Real y = GAMMA_FOR_Y;
			Real z = GAMMA_FOR_Z;

			for(soluteSite = 0; soluteSite<Nsolute; soluteSite++)
			{
				Real x1 = m_soluteCoordinates->getX()[soluteSite];
				Real y1 = m_soluteCoordinates->getY()[soluteSite];
				Real z1 = m_soluteCoordinates->getZ()[soluteSite];

				Real r2 = (x-x1)*(x-x1) + (y-y1)*(y-y1) + (z-z1)*(z-z1);
				Real MaxR2 = m_radii[soluteSite] * m_radii[soluteSite];

				if(r2 < MaxR2)
				{
					*c_ptr  = -*gamma_ptr - 1;
				}


			}

			c_ptr++;
			gamma_ptr++;
		}
		END_GAMMA_FOR
	} //solvent site


}

HardSphereClosureFactory3DRISM::HardSphereClosureFactory3DRISM(
					const char *radiiFile,
					const char *distanceUnits,
					ClosureFactory3DRISM *subClosureFactory,
					GridIndependentInterface3DRISM *gridIndependent)
{
	m_subClosureFactory = subClosureFactory;
	m_gridIndependent  = gridIndependent;

	Integer nlin,ncol;
	readDoubleTable	( 
			radiiFile,	//const char *fname,
			&nlin,		//Integer *nlin,	//out
			&ncol,		//Integer *ncol,	//out
			&m_radii	//Real **result //out, will be allocated
			);

//	if(nlin!=soluteCoordinates->getNumSites())
//	{
//		throw new Exception(this,"HardSphereClosureFactory3DRISM: invalid input radii file");
//	}

	Real kDistance = Units::distanceUnits()->unit2unit(distanceUnits,"Bohr");

	Integer i;
	for(i=0;i<nlin;i++)
		m_radii[i]*=kDistance;

}

HardSphereClosureFactory3DRISM::~HardSphereClosureFactory3DRISM()
{
	if(m_radii) free(m_radii);
}

Closure3DRISM *HardSphereClosureFactory3DRISM::createClosure3DRISM(Solution3DRISMR *betaUshort)
{

	

	Closure3DRISM *subClosure = m_subClosureFactory->createClosure3DRISM(betaUshort);
	Closure3DRISM *closure = new HardSphereClosure3DRISM(
							m_radii,	// Real *radii ,
				 			subClosure,	//Closure3DRISM *subClosure,
				 			m_gridIndependent->getSoluteCoordinates()	//MoleculeCoordinates *soluteCoordinates 
					);
	closure->addToDeleteList(subClosure);
	return closure;	
}

