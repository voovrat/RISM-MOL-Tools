#include "openOrDie.h"

#include <stdio.h>

FILE *openOrDie(const char *file,const char *prm)
{
FILE *f = fopen(file,prm);
static char error[1024];

if(!f) 
{
	sprintf(error,"cannot open %s\n",file);
	throw error;
}
return f;
}

