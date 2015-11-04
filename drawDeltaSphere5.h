#ifndef drawDeltaSphere5_h
#define drawDeltaSphere5_h

#include "Settings.h"

class Grid3DRISM;

// Values are the cube-sphere cross section, assuming that the function is linear
void	drawDeltaSphere5(Real R,
			Real *data,
			Grid3DRISM *,
			Real dtheta = 0.001,
			Real dphi = 0.001);


#endif
