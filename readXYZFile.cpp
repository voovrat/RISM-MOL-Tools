#include "readXYZFile.h"

#include <stdio.h>
#include <stdlib.h>

#include "AtomRecord.h"


void readXYZFile(	const char *file,
			std::list<AtomRecord> *atomList)
{
char str[256];
static char error[256];

FILE *f = fopen(file,"r");
if(!f)
{
	sprintf(error,"readXYZFile: cannot open input file %s\n",file);
	throw error;
}

fgets(str,256,f); // 1st line
fgets(str,256,f); // 2nd line

int line =2;
int N;
int id=0;
while(!feof(f))
{
AtomRecord atomRecord;

if(!fgets(str,256,f)) break;

 N = sscanf(str,"%s%lf%lf%lf",atomRecord.element,&atomRecord.x,&atomRecord.y,&atomRecord.z);
line++;
id++;
if(N==0) break;

if(N<4) 
{
	sprintf(error,"Incorect format at line %d\n",line);
	throw error;
}
atomRecord.id=id;

atomList->push_back(atomRecord);

}//while !feof

fclose(f);

}

/*
main()
{
std::list<AtomRecord> atomList;

readXYZFile("a.xyz",&atomList);

std::list<AtomRecord>::iterator it;
for(it=atomList.begin(); it!=atomList.end(); it++)
{
	AtomRecord atomRecord = *it;
	printf("%d %s : %lg %lg %lg\n",	atomRecord.id,
					atomRecord.element,
					atomRecord.x,
					atomRecord.y,
					atomRecord.z);}

}
*/
