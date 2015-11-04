#ifndef IterationDivergeException_h
#define IterationDivergeException_h

#include "Exception.h"

class IterationDivergeException : public Exception
{
public:
	IterationDivergeException(Object *sender, const char *string)
	: Exception(sender,string)
	{
		m_exceptionName = (char*)"IterationDivergeException";
	}
};

#endif
