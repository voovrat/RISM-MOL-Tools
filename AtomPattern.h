#ifndef AtomPattern_h
#define AtomPattern_h

#include <list>
#include <stdio.h>

#include "Object.h"

#include <string>

class ParseAtom;

class AtomPattern : public Object
{
public:

AtomPattern *m_image;
char m_element[8];
char m_forceFieldName[256];
int m_isTerminal;
int m_label;

std::list<AtomPattern *>  m_connectedTo;


AtomPattern(	const char *element="",
		int isTerminal=0,
		const char *forceFieldName="" );


void clearVisited(std::list<AtomPattern *> *visited);

int match( AtomPattern *subPattern );

int match( 	AtomPattern *subPattern , 
		std::list<AtomPattern *> *visited 
	 );

void rootToString(std::string *str);
void allToString(std::string *str);

};

#endif
