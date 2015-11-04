#ifndef calculateGFFreeEnergy_h
#define calculateGFFreeEnergy_h

#include "Settings.h"

class Solution3DRISMR;

double	calculateGFFreeEnergy(	Solution3DRISMR *gamma,	
					Solution3DRISMR *c,
					Solution3DRISMR *minusBetaUlong,
					Real kBT,
					Real *densities,
					Integer *multiplicities
			 	);


#endif
