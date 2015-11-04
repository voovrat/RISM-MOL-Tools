#include "upperString.h"

#include <ctype.h>

void upperString( 	char *dst,
			const char *src)
{
	while(*src)
	{
		*dst = toupper(*src);
		src++; dst++;
	}
	*dst=0;
}
