#ifndef buildAnalyticalTheta2_h
#define buildAnalyticalTheta2_h

#include "Settings.h"

class MoleculeCoordinates;
class MoleculeCharges;
class TabFunction;
class SiteMultiplicities;
class Solution3DRISMR;
class SigmaEpsilonTable;


void buildAnalyticalTheta2(
			MoleculeCoordinates *soluteCoors,
			MoleculeCharges *soluteCharges,
			MoleculeCharges *solventCharges,
			SiteMultiplicities *siteMultiplicities,
			TabFunction  ***phiIndex,
			TabFunction  ***phiLJIndex,  // NULL if no LJ correction
			SigmaEpsilonTable *sigmaEpsilonTable,
			Real **chiMultipliers,
			Solution3DRISMR *theta			// out
		   );
#endif
