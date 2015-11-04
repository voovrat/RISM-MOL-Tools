#include "Statistics.h"
#include "Timer.h"

Statistics::Statistics()
{
	m_timer = new Timer();
	m_iterationTime = 0;
}

Statistics::~Statistics()
{
	NULL_DELETE(m_timer);
}

Statistics *Statistics::getInstance()
{
	static Statistics *instance = NULL;
	if(!instance) 
		instance = new Statistics();
	
	return instance;
}

void Statistics::startIteration()
{
	m_timer->tic();
}

void Statistics::endIteration()
{
	m_iterationTime += m_timer->toc();
}

