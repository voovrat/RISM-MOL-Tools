#ifndef findProbableGmaxRegions_h
#define findProbableGmaxRegions_h

#include "Settings.h"
class Grid3DRISM;

void findProbableGmaxRegions(	Real **g_index, // array of g functions
				Grid3DRISM *grid,
				Integer Nsites,	// number of g functions
				Real treshold,	
				Real radius,	// radius of the filter (typically: max distance between the molecule's atoms )
				Integer *probableGmax //out (is not allocated)
				);	

#endif
