#ifndef buildKSphere_h
#define buildKSphere_h

#include "Settings.h"
#include <complex>

class Grid3DRISM;

void	buildKSphere(Real R,
		     std::complex<Real> *data,
			Grid3DRISM *grid
		   );
#endif
