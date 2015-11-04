#ifndef buildPotential2_h
#define buildPotential2_h

#include "Settings.h"


//build Potential with averaging over grid cell
class MoleculeCoordinates;
class SiteSitePotential;
class Solution3DRISMR;

void buildPotential2 (
	MoleculeCoordinates *soluteCoors,
	SiteSitePotential *siteSitePotential,
	Solution3DRISMR *potential, // output
	Real divider = AVERAGING_DIVIDER
);




#endif
