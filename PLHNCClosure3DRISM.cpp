#include "PLHNCClosure3DRISM.h"

//#include "calculateBeta.h"
#include "Solution3DRISMR.h"

PLHNCClosure3DRISM::PLHNCClosure3DRISM(
				Solution3DRISMR *betaUshort
				)
{
	m_betaUShort = betaUshort;
}

void PLHNCClosure3DRISM::calculateClosure(Solution3DRISMR *gamma,
					Solution3DRISMR *c //out
					)
{
	Integer N = gamma->getTotalSizeOfGamma();

	Real *c_ptr = c->getRawData();
	Real *gamma_ptr = gamma->getRawData();
	Real *betaU_ptr = m_betaUShort->getRawData();

	while(N--)
	{
		Real Xi = *betaU_ptr + *gamma_ptr;

		if(Xi<0)
		{
			*c_ptr = exp(Xi)-*gamma_ptr - 1;
		}
		else {
			*c_ptr = *betaU_ptr;
		}

		c_ptr++;
		gamma_ptr++;
		betaU_ptr++;
	}
}

