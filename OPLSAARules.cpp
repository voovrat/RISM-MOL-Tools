#include "OPLSAARules.h"

#include <math.h>

void OPLSAARules::operator()(
		Real sigma1,
		Real epsilon1, 
		Real sigma2,
		Real epsilon2,
		Real *sigma12,
		Real *epsilon12
		)
{
	*sigma12 = sqrt(sigma1*sigma2);
	*epsilon12 = sqrt(epsilon1*epsilon2);
}
