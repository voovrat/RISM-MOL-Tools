#ifndef normalizeGrid_h
#define normalizeGrid_h

#include "Settings.h"
class Grid3DRISM;

//re-arrange the elements in "in" to have the descending grid 
// ( from -N/2+1 ... N/2 in each dimension )
void normalizeGrid(	Real *in,
			Grid3DRISM *grid,
			Real *out,
			Real *gridPointsX = NULL, // grid 
			Real *gridPointsY = NULL,
			Real *gridPointsZ = NULL
		);

#endif

