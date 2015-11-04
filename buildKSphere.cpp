#include "buildKSphere.h"

#include <math.h>
#include "Grid3DRISM.h"

void	buildKSphere(	Real R,
		     	std::complex<Real> *data,
			Grid3DRISM *grid
		   )
{
std::complex<Real> *ptr;


ptr = data;
KGAMMA_FOR(grid)
{
	Real K = KGAMMA_FOR_KR;

	
	if(K*R!=0)
		*ptr =  sin(K*R) / K/R ;
	else
		*ptr = 1;

	ptr++;
}
END_KGAMMA_FOR

}
