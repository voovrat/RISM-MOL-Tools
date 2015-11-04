#ifndef conv3D_h
#define conv3D_h

#include "Settings.h"
class Grid3DRISM;

void conv3D(	Real *A,
		Real *B,
		Grid3DRISM *grid,
		Real *C // out: C=conv(A,B)
		);

#endif

