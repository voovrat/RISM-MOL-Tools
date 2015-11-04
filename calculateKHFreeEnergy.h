#ifndef calculateKHFreeEnergy_h
#define calculateKHFreeEnergy_h

#include "Settings.h"

class Solution3DRISMR;

double	calculateKHFreeEnergy(	Solution3DRISMR *gamma,	
					Solution3DRISMR *c,
					Solution3DRISMR *minusBetaUlong,
					Real kBT,
					Real *densities,
					Integer *multiplicities
			 	);


#endif
