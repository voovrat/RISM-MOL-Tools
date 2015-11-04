#ifndef calculateMyHNCFreeEnergy_h
#define calculateMyHNCFreeEnergy_h

#include "Settings.h"

class Solution3DRISMR;

double	calculateMyHNCFreeEnergy(	Solution3DRISMR *gamma,	
					Solution3DRISMR *c,
					Solution3DRISMR *minusBetaUlong,
					Real kBT,
					Real *densities,
					Integer *multiplicities
			 	);


#endif
