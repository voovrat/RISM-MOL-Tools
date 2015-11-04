#ifndef ParseStringException_h
#define ParseStringException_h

#include "Exception.h"

class ParseStringException : public Exception
{
public:
	ParseStringException(Object *sender,const char *str) :
	Exception(sender,str)
	{
		m_exceptionName = (const char *)"ParseStringException";
	}

};

#endif
