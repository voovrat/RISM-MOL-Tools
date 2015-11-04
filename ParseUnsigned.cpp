#include "ParseUnsigned.h"

#include <stdlib.h>
#include "StringParser.h"

Integer ParseUnsigned::parse(StringParser *sp)
{
	const char *ptr = sp->getPtr();

	while(expectChars(sp,"0123456789")) ;

	m_integer=0;

	if(ptr==sp->getPtr()) return 0;

	while(ptr<sp->getPtr())
	{
		m_integer = m_integer*10 + (*ptr - '0');
		ptr++;
	}

	return 1;	

}
