#ifndef Statistics_h
#define Statistics_h

#include "Object.h"
#include "Settings.h"
class Timer;

class Statistics : public Object
{
protected:
	Statistics();
	
	
	Time m_iterationTime;
	Timer *m_timer;
public:
	static Statistics *getInstance();
	virtual ~Statistics();

	void startIteration();
	void endIteration();

	Time  getIterationTime()
	{
		return m_iterationTime;
	}


};


#endif
