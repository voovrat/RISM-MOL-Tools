#ifndef Pointer_h
#define Pointer_h

#include <stdlib.h>
#include "Object.h"

class Pointer : public Object
{
protected:
	void *m_ptr;
public:
	Pointer(void *ptr)
	{
		m_ptr = ptr;
	}

	virtual ~Pointer()
	{
		free(m_ptr);
	}


};


#endif
