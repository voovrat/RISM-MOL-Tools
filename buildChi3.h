#ifndef buildChi3_h
#define buildChi3_h

#include "Settings.h"

class TabFunction;
class Solution3DRISMK;
class OmegaData;

// because for multi-component systems if density[i] != density[j]
// chi[i][j] = density[i]*h[i][j] and 
// chi[j][i] = density[j]*h[j][i]
// because we do not want to store 2 times more functions, it is better to have
// a pre-multipliers for the chi functions

// if densities[i] == densities[j] than chiMultipliers[i][j]=1, and chi[j][i] is pre-multiplied by density
// else  chiMultipliers[i][j]= densities[i] and
//	chiMultipliers[j][i] = densities[j] and
// chi[i][j] is NOT pre-multiplied by density
void buildChi3(TabFunction **rdfs,// array size= numSolventSites*(numSolventSites-1)/2
				  // elements g11, g12.. g1N, g22,...g2N... gNN
		Integer numSolventSites,
		OmegaData *omega,
		Real *densities,	//in Bohr^-3
		Solution3DRISMK **chi3D,	//out, coresponds to chi
		Solution3DRISMK ***chiIndex,	//out, numSolventSites*numSolventSites array
						// chiIndex[i][j] contains chi[i][j]
		Real **chiMultipliers		//out
		);

#endif
