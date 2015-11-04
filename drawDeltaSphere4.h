#ifndef drawDeltaSphere4_h
#define drawDeltaSphere4_h

#include "Settings.h"

class Grid3DRISM;

// Values are proportional to the cube-sphere cross section
void	drawDeltaSphere4(Real R,
			Real *data,
			Grid3DRISM *,
			Real dtheta = 0.001,
			Real dphi = 0.001);


#endif
