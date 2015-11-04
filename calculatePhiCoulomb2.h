#ifndef calculatePhiCoulomb2_h
#define calculatePhiCoulomb2_h


#include "Settings.h"

class Grid1DRISM;
class TabFunction; 

// ----------  Calculating Phi a Coulomb Part (Phi):
// 		d3ifft( 1/k^2 exp(-k^2/4t^2) * chi[i][j] )

void calculatePhiCoulomb2(	Grid1DRISM *grid,
				Real	KBT,
				TabFunction ***analyticChiIndex,
				Real **chiMultipliers,
				Real ngCoeff,
				Integer numSolventSites,
				TabFunction **phi,	//out
				TabFunction ***phiIndex //out
			);

#endif
