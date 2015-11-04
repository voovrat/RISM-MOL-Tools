#ifndef PairParameter_h
#define PairParameter_h

#include <stdio.h>
#include "Parameter.h"

class PairParameter : public Parameter
{
protected:
	Parameter *m_first,*m_second;
public:

        PairParameter() {m_first = NULL; m_second=NULL;}

        ~PairParameter() {}

	virtual Integer getType()
	{
		return PAIR;
	}

	virtual Parameter *clone();

	virtual Parameter *retainCopy()
	{
		this->retain();
		m_first->retainCopy();
		m_second->retainCopy();
		return this;
	}


        Parameter *getFirstPtr()  
	{ 
		return m_first;
        }

	Parameter *getSecondPtr()
	{
		return m_second;
 	}
	
        void setFirstPtr(Parameter *first)  
	{ 
		m_first = first;
        }

	void setSecondPtr(Parameter *second)
	{
		m_second = second;
 	}
 
	std::string toString()
	{
		return "("+m_first->toString()+","+m_second->toString() + ")";
	}

};

#endif
