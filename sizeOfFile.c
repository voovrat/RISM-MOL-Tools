#include "sizeOfFile.h"

#include <stdio.h>

unsigned long sizeOfFile(const char *fname)
{
	unsigned long size;

	FILE *f = fopen(fname,"rb");
	if(!f)
		return 0;

	fseek(f,0,SEEK_END);

	size = ftell(f);

	fclose(f);

	return size;
}
