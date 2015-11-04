#ifndef buildPotential4_h
#define buildPotential4_h

#include "Settings.h"


//build Potential with preserving height of the first peak 
// (or equivalent: depth of the first U minima)
class MoleculeCoordinates;
class SiteSitePotential;
class Solution3DRISMR;

void buildPotential4 (
	MoleculeCoordinates *soluteCoors,
	SiteSitePotential *siteSitePotential,
	Real beta,
	Solution3DRISMR *potential, // output
	Integer divider = AVERAGING_DIVIDER
);




#endif
