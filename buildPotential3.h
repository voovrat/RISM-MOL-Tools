#ifndef buildPotential3_h
#define buildPotential3_h

#include "Settings.h"


//build Potential with averaging over grid cell
class MoleculeCoordinates;
class SiteSitePotential;
class Solution3DRISMR;

void buildPotential3 (
	MoleculeCoordinates *soluteCoors,
	SiteSitePotential *siteSitePotential,
	Real beta,
	Solution3DRISMR *potential, // output
	Real divider = AVERAGING_DIVIDER
);




#endif
