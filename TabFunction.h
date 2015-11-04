#ifndef TabFunction_h
#define TabFunction_h

#include <stdio.h>

#include "UnaryFunction.h"

class TabFunction : public UnaryFunction<Real,Real>
{
protected:

	Real *m_tab;
	Integer m_N;
	Real m_x0,m_1dx,m_dx05;

public:

	TabFunction()
	{
		m_tab=NULL;
		m_N=0;
		m_x0=0;
		m_1dx = 0;
		m_dx05=0;
	}

	Real *getTab()
	{
		return m_tab;
	}
	
	Integer getTabSize()
	{
		return m_N;
	}
	
	Real getTabStep()
	{
		return 1/m_1dx;
	}
	
	virtual void init(Real *tab,Integer N,Real x0,Real dx)
	{
		cleanUpDeleteList();

		m_tab = tab;
		m_N = N;
		m_x0=x0;
		m_1dx = 1/dx;
		m_dx05 = dx*0.5;
	}


	virtual Real operator()(Real x)
	{
		Integer m = (Integer)( (x-m_x0 + m_dx05)*m_1dx );
		if(m<0) m=0;
		if(m>=m_N) m=m_N-1;

		return m_tab[m];
	}

};


#endif
