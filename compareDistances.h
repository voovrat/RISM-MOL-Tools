#ifndef compareDistances_h
#define compareDistances_h

#include "Settings.h"
#include <math.h>

// if distances from two atoms to all others are the same - atoms are identical and can be joined

inline Integer compareDistances(Real *distances,
				Integer Nsites,
				Integer lineA,
				Integer lineB,
				Real eps = 1e-2 )
{

Real *pA = distances + lineA * Nsites;
Real *pB = distances + lineB * Nsites;

Integer i;
for(i=0;i<Nsites;i++,pA++,pB++)
{
	if( i==lineA || i==lineB )  continue;
	if( fabs( *pA - *pB) > eps ) return 0;
}

return 1;

}

#endif
