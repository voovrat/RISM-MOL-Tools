#ifndef calculateHNCFreeEnergy_h
#define calculateHNCFreeEnergy_h

#include "Settings.h"

class Solution3DRISMR;

double	calculateHNCFreeEnergy(	Solution3DRISMR *gamma,	
					Solution3DRISMR *c,
					Solution3DRISMR *minusBetaUlong,
					Real kBT,
					Real *densities,
					Integer *multiplicities
			 	);


#endif
