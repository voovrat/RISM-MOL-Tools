#ifndef Timer_h
#define Timer_h


#include "Object.h"
#include "Settings.h"

class Timer : public Object
{
protected:
	Time m_t0;
public:
	Timer()
	{
		m_t0 = 0;
	}
	
	Time tic();
	Time  toc();

};

#endif
