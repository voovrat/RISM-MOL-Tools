#include "getPath.h"

#include <stdlib.h>

#include <list>
#include <string>
#include "StringParser.h"

void getPath(	const char *pathstr, 
		std::list<std::string> *pathList
		)
{char pathItem[1024];

StringParser sp(pathstr);

while(!sp.isOver())
{
	sp.getUntil(	":", //const char *delim,
			pathItem,	//char *str,
			1024	//Integer maxChar
		);

	std::string pathItemString = pathItem;
	pathList->push_back(pathItemString);
	
	sp.skipChars(":");

}

}
/*
#include <stdio.h>
#include <stdlib.h>

main()
{
std::list<std::string> path;

getPath( getenv("PATH"), &path);

puts(getenv("PATH"));

std::list<std::string>::iterator it;
for(it=path.begin(); it!=path.end(); it++)
{
	printf("[%s]\n",(*it).c_str());
}

return 0;
}
*/
