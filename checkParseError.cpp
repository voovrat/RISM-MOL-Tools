#include "checkParseError.h"

#include "ParseStringException.h"
#include "Pointer.h"

void checkParseError(StringParser *sp,char *S)
{
	if(sp->getError())
	{
		Exception *e=new ParseStringException(NULL,sp->getPtr());

		e->addToDeleteList(new Pointer(S));
		throw e;
	}
}
