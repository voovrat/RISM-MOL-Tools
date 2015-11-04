#include "readFile.h"
#include "openOrDie.h"
#include "sizeOfFile.h"

#include <stdlib.h>

char *readFile(const char *file)
{
FILE *f = openOrDie(file,"r");
int N = sizeOfFile(file);
char *str =(char *) malloc(N+1);
fread(str,N,1,f);
str[N]=0;
return str;
}
