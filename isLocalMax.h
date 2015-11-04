#ifndef isLocalMax_h
#define isLocalMax_h

#include "Settings.h"
class Grid3DRISM;

Integer isLocalMax(	Real *data,	
			Grid3DRISM *grid,
			Real x0,
			Real y0,
			Real z0,
			Real radius );

#endif

