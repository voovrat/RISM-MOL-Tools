#ifndef Exception_h
#define Exception_h

#include "Object.h"
#include <string.h>

class Exception : public Object
{
protected:

	const char *m_exceptionName;
	char m_string[1024];
	Object *m_sender;

public:
	Exception(Object *sender,const char *string)
	{
		m_exceptionName = (const char *)"Exception";
		m_sender = sender;
		strncpy(m_string,(char *)string,1024);
	}

	virtual  const char *toString()
	{
		return m_string;
	}

	virtual const char *getName()
	{
		return m_exceptionName;
	}
	
};

#endif
