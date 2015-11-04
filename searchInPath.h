#ifndef searchInPath_h
#define searchInPath_h

#include <list>
#include <string>


int searchInPath(	const char *fname,
			std::list<std::string> *pathList,
			char *fullName,
			int maxN
		 );

#endif

