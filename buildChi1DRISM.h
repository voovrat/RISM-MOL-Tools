#ifndef buildChi1DRISM_h
#define buildChi1DRISM_h

#include "Settings.h"

class TabFunction;
class OmegaData;

void buildChi1DRISM(TabFunction **rdfs,// array size= numSolventSites*(numSolventSites-1)/2
				  // elements g11, g12.. g1N, g22,...g2N... gNN
		Integer numSolventSites,
		OmegaData *omega,
		Real *densities,	//in Bohr^-3
		TabFunction **chi,	//out, coresponds to chi
		TabFunction ***chiIndex,	//out, numSolventSites*numSolventSites array
						// chiIndex[i][j] contains chi[i][j]
		Real **chiMultipliers // out
		);

#endif
