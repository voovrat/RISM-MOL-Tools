#ifndef buildRDF4_h
#define buildRDF4_h

#include "Settings.h"


//build Potential with averaging over grid cell
class MoleculeCoordinates;
class SiteSitePotential;
class Solution3DRISMR;

void buildRDF4 (
	MoleculeCoordinates *soluteCoors,
	SiteSitePotential *siteSitePotential,
//	Real beta,
	Solution3DRISMR *potential, // output
	Real divider = AVERAGING_DIVIDER
);




#endif
