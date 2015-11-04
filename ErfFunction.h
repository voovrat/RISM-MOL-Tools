#ifndef ErfFunction_h
#define ErfFunction_h

#include "OddFunction.h"
#include "TabFunction.h"

class ErfFunction : public OddFunction<Real>
{
protected:
	static Real *m_tab;
	static Integer m_N;
	static Real m_dx;
	static Real m_x0;

	TabFunction m_erfTab;

	ErfFunction() : OddFunction<Real>(&m_erfTab)
	{
		m_erfTab.init(	m_tab,	//Real *tab,
				m_N,	//Integer N,
				m_x0,	//Real x0,
				m_dx	//Real dx)
		);
		
	}

public:
	static ErfFunction *getInstance()
	{
		static ErfFunction *instance=NULL;
		if(!instance)
			instance = new ErfFunction();

		return instance;
	}

};


#endif
