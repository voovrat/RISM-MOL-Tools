#include "strcpyUntil.h"

char *strcpyUntil(	char *dst,
			const char *src,
			const char *separators
		)
{
const char *sep;

while(*src)
{

for(sep=separators; *sep; sep++)
{
	if(*src == *sep) break;
}
if(*sep) break;

*dst = *src;
src++;dst++;
}

*dst=0;
return dst;

}

