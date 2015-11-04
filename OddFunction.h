#ifndef OddFunction_h
#define OddFunction_h

#include "UnaryFunction.h"

template<class T>
class OddFunction : public UnaryFunction<Real,T>
{
	UnaryFunction<Real,T> *m_subFunction; //defined on [0,inf)

public:
	OddFunction(UnaryFunction<Real,T> *subFunction)
	{
		m_subFunction = subFunction;
	}

	T operator()(Real x)
	{
		if(x>=0)
			return (*m_subFunction)(x);
		else
			return -(*m_subFunction)(-x);
	}

};

#endif
