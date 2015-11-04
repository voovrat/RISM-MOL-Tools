#ifndef OmegaK_h
#define OmegaK_h

#include "Settings.h"
#include "UnaryFunction.h"

class OmegaK : public UnaryFunction< Real ,Real>
{
protected:
	Real m_r,m_coeff;
public:
	OmegaK(Real r,Real coeff=1)
	{
		m_r = r;
		m_coeff = coeff;
	}

	Real operator()(Real k)
	{
		return (k<MIN_K || m_r<MIN_DISTANCE) ? m_coeff : m_coeff*sin(k*m_r)/k/m_r;
	}

};

#endif
