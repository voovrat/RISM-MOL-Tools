#ifndef calculateExcludedVolume_h
#define calculateExcludedVolume_h

#include "Settings.h"

class Solution3DRISMR;
class TabFunction;


// excluded volume is calculated by formula:
// V = 1/rho + int ( h_solv0) - 1/Nsites sum_i int h_solute[i] 
// Function works properly only for one component solvents 
// (however, as i understand, if we calculate excluded volume for one component - it automatically be the same for all others... )
double	calculateExcludedVolume(	TabFunction **solventRDFs, 
					Solution3DRISMR *gamma,	
					Solution3DRISMR *c,
					Real *densities,  
					Integer *multiplicities
			 	);


#endif
