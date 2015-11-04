#include "readPDBFile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AtomRecord.h"


void readPDBFile(	const char *file,
			std::list<AtomRecord> *atomList)
{
char str[256];
static char error[256];

FILE *f = fopen(file,"r");
if(!f)
{
	sprintf(error,"readPDBFile: cannot open input file %s\n",file);
	throw error;
}

char recname[7];
char atom[3];
char coordinates[25];
char serial[6];

int line =0;
int N;
while(!feof(f))
{
AtomRecord atomRecord;

if(!fgets(str,256,f)) break;
line++;

strncpy(recname,str,6); recname[6]=0;
if( 	(strcmp(recname,"ATOM  ")!=0 )
  && 	(strcmp(recname,"HETATM")!=0)
  ) continue;

strncpy(serial,str+6,5); serial[5]=0;
sscanf(serial,"%d",&atomRecord.id);

strncpy(atom,str+12,2); atom[2]=0;
int i;
for(i=0;i<2;i++)
{
if(!  ( (atom[i]>='a' && atom[i]<='z') ||
        (atom[i]>='A' && atom[i]<='Z') )
  ) atom[i]=' ';
}

sscanf(atom,"%s",atomRecord.element);

strncpy(coordinates,str+30,24); coordinates[24]=0;
sscanf(coordinates,"%lf%lf%lf",&atomRecord.x,&atomRecord.y,&atomRecord.z);

atomList->push_back(atomRecord);

}//while !feof

fclose(f);

}

/*
main()
{
std::list<AtomRecord> atomList;

readPDBFile("benzene.pdb",&atomList);

std::list<AtomRecord>::iterator it;
for(it=atomList.begin(); it!=atomList.end(); it++)
{
	AtomRecord atomRecord = *it;
	printf("%d %s : %lg %lg %lg\n",atomRecord.id,
					atomRecord.element,
					atomRecord.x,
					atomRecord.y,
					atomRecord.z);
}

}
*/
