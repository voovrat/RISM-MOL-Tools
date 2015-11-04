#ifndef PlainDoubleParameter_h
#define PlainDoubleParameter_h

#include "DoubleParameter.h"

class PlainDoubleParameter : public DoubleParameter
{
protected:
	Real m_value;

public:

	PlainDoubleParameter(Real value)
	{
		m_value = value;
	}

	virtual Real getDouble()
	{
		return m_value;
	}

	virtual void setDouble(Real value)
	{
		m_value = value;
	}

	virtual	Parameter *clone()
	{
		return new PlainDoubleParameter(m_value);
	}
};

#endif
