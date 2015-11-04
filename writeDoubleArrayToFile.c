#include "writeDoubleArrayToFile.h"
#include <stdio.h>

#include "Settings.h"

void writeDoubleArrayToFile(const char *fname,Real *x,Integer N)
{
FILE *f;
int i;

f = fopen(fname,"w");

for(i=0;i<N;i++)
	fprintf(f,"%le\n",(double)x[i]);

fclose(f);

}
