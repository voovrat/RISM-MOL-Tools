#ifndef GridIndependentInterface3DRISM_h
#define GridIndependentInterface3DRISM_h

#include "GridIndependentData.h"

class MoleculeCoordinates;
class MoleculeLJParameters;
class MoleculeCharges;
class SiteMultiplicities;
class SiteSitePotential;
class SiteDensities;

class GridIndependentInterface3DRISM : public GridIndependentData
{
public:

	// SoluteData
	virtual MoleculeCoordinates 	*getSoluteCoordinates()=0;
	virtual MoleculeLJParameters	*getSoluteLJParameters()=0;
	virtual MoleculeCharges 	*getSoluteCharges()=0;

	// Solvent Data
	virtual MoleculeLJParameters	*getSolventLJParameters()=0;
	virtual MoleculeCharges		*getSolventCharges()=0;
	virtual SiteMultiplicities	*getSiteMultiplicities()=0;
	virtual SiteDensities		*getSiteDensities()=0;
	
	// Potentials
	virtual SiteSitePotential	*getNgSiteSitePotential()=0;
	virtual SiteSitePotential	*getShortSiteSitePotential()=0;

	// Physical properties
	virtual Real getKBT()=0;

};


#endif
