#include "AtomPattern.h"

#include <string.h>
#include <stdio.h>
#include "generatePermutivities.h"



AtomPattern::AtomPattern(const char *element,int isTerminal,const char *forceFieldName)
{
	m_image=NULL;
	strcpy(m_element,element);
	m_isTerminal = isTerminal;
	strcpy(m_forceFieldName,forceFieldName);
}

void AtomPattern::clearVisited(std::list<AtomPattern *> *visited)
{
std::list<AtomPattern *>::iterator it;
	
for(it=visited->begin(); it!=visited->end(); it++)
{
	(*it)->m_image=NULL;
}
		
}

int AtomPattern::match(	AtomPattern *subPattern)
{

int R;
std::list<AtomPattern *> visited;
R = match(subPattern,&visited);

clearVisited(&visited);		

return R;
}


#include <stdio.h>

int AtomPattern::match( AtomPattern *subPattern,
			std::list<AtomPattern *> *visited 
	 )
{
 
//fprintf(stderr,"AtomPattern::match %d %s\n",m_label,m_element);

if(m_image!=NULL)
{
	return 	m_image == subPattern;
}

if(strcmp(subPattern->m_element,"R")==0)
	return 1;

if(strcmp(m_element,subPattern->m_element)!=0 
	&& strcmp(subPattern->m_element,"*")!=0)
		return 0;


if(subPattern->m_isTerminal) return 1;

if(m_connectedTo.size() != subPattern->m_connectedTo.size())
	return 0;

m_image = subPattern;
visited->push_back(this);


std::list<void *> items;
std::list< std::list<void *> *> permutivities;

std::list<AtomPattern *>::iterator it;

for(it = m_connectedTo.begin(); it!=m_connectedTo.end(); it++)
{
	items.push_back((void *)*it);
}

generatePermutivities(	&items,	//std::list<void *>  *items,
			&permutivities //std::list< std::list<void *> *> *permutivities /*out, should be empty on input*/
			   );

std::list<AtomPattern *> subvisited;
int result = 0;
std::list<std::list<void *> *>::iterator permIt;

for(permIt=permutivities.begin(); permIt!=permutivities.end(); permIt++)
{
	std::list<void *>::iterator itemIterator;
	std::list<AtomPattern *>::iterator subIterator;

	for(	itemIterator = (*permIt)->begin(), subIterator = subPattern->m_connectedTo.begin();
	    	itemIterator!=(*permIt)->end(); 
		itemIterator++, subIterator++	)
	{
		AtomPattern *child = (AtomPattern *)*itemIterator;
		if(!child->match(*subIterator,&subvisited))
		{
			break;
		}

	}// children 

	
	if( itemIterator == (*permIt)->end())
	{
		result = 1; break;
	}

	clearVisited(&subvisited);
	subvisited.clear();

}//permutivities

if(result)
{
	visited->insert(visited->end(),subvisited.begin(),subvisited.end());
}


for(permIt=permutivities.begin(); permIt!=permutivities.end(); permIt++)
{
	delete *permIt;
}


return result;

}

void AtomPattern::rootToString(std::string *str)
{

char tmp[20];
(*str)+=m_element;
(*str)+="(";
sprintf(tmp,"%d",m_label);
(*str)+=tmp;
(*str)+=")";

if(m_isTerminal) (*str)+='T';

}

void AtomPattern::allToString(std::string *str)
{
rootToString(str);
std::list<AtomPattern *>::iterator it;
for(it=m_connectedTo.begin(); it!=m_connectedTo.end(); it++)
{
	(*str)+=' ';
	(*it)->rootToString(str);
}
(*str)+='\n';
}
