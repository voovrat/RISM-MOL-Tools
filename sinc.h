#ifndef sinc_h
#define sinc_h

#include <math.h>
#include "Settings.h"

inline Real sinc(Real x)
{
 	return x<1e-6 ? 1 : sin(x)/x;
}


#endif
