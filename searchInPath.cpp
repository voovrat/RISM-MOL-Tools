#include <stdio.h>
#include <string.h>
#include <list>
#include <string>


int searchInPath(	const char *fname,
			std::list<std::string> *pathList,
			char *fullName,
			int maxN
		 )
{
FILE *f;
f=fopen(fname,"r");

if(f)
{
	fclose(f); 
	strncpy(fullName,fname,maxN);
	return 1;
}

char fullPath[1024];

std::list<std::string>::iterator it;
for(it=pathList->begin(); it!=pathList->end(); it++)
{
	sprintf(fullPath,"%s/%s",(*it).c_str(),fname);
	f=fopen(fullPath,"r");
	if(f)
	{
		fclose(f);
		strncpy(fullName,fullPath,maxN);
		return 1;
	}
}

fullName[0]=0;
return 0;
}

/*
#include "getPath.h"
#include <stdlib.h>

main()
{

std::list<std::string> pathList;

getPath(getenv("PATH"),	//const char *pathstr, 
	&pathList	//std::list<std::string> *pathList
	);

char fullName[256];
int R=searchInPath(	"ffopls.pat",	//const char *fname,
		&pathList,	//std::list<std::string> *pathList,
		fullName,	//char *fullName,
		256		//int maxN
		 );
if(R) 
 puts(fullName);
else 
 puts("FILE NOT FOUND");
return 0;

}
*/
