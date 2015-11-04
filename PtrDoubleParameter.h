#ifndef PtrDoubleParameter_h
#define PtrDoubleParameter_h

#include "DoubleParameter.h"


class PtrDoubleParameter : public DoubleParameter
{
protected:
	Real *m_pvalue;

public:

	PtrDoubleParameter(Real *pvalue)
	{
		m_pvalue = pvalue;
	}

	virtual Real getDouble()
	{
		return *m_pvalue;
	}

	virtual void setDouble(Real value)
	{
		*m_pvalue = value;
	}

	virtual Parameter *clone()
	{
		return new PtrDoubleParameter(m_pvalue);
	}
};



#endif
