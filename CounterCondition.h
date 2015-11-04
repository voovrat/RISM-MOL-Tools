#ifndef CounterCondition_h
#define CounterCondition_h

#include "Condition.h"

class CounterCondition : public Condition
{
protected:
	Integer m_N;
public:
	CounterCondition(Integer N)
	{	
		m_N = N;
	}

	virtual Integer check(Object* a,Object *b)
	{
		if(m_N<=0) return 1;
		m_N--;
		return 0;
	}
	
};

#endif
