#include "Timer.h"

#include <time.h>

Time Timer::tic()
{
	m_t0 = (Time)time(NULL);
	return m_t0;
}

Time Timer::toc()
{
	Time t1 = (Time)time(NULL);
	return t1-m_t0;
}

