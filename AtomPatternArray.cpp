#include "AtomPatternArray.h"

#include "AtomPattern.h"

#include <string.h>
#include <stdlib.h>

AtomPatternArray::AtomPatternArray()
{
m_patternName[0]=0;
m_patternArray = NULL;
m_N=0;
}



void AtomPatternArray::alloc(Integer N)
{
	dealloc();

	m_N = N;
	m_patternArray = new AtomPattern*[N];
	int i;
	for(i=0;i<N;i++)
		m_patternArray[i] = new AtomPattern();
}

void AtomPatternArray::dealloc()
{
	if(m_patternArray)
	{
		int i;
		for(i=0;i<m_N;i++)
		{
			NULL_DELETE(m_patternArray[i]);
		}
		delete [] m_patternArray;
		m_patternArray = NULL;
		m_N=0;
	}

}

void AtomPatternArray::setPatternName(const char *name)
{
	strncpy(m_patternName,name,256);
}


void AtomPatternArray::getPatternName(char *dst,int N)
{
	strncpy(dst,m_patternName,N);
}

void AtomPatternArray::print()
{
	printf("%s:\n",getPatternName());

	int i;

	for(i=0;i<m_N;i++)
	{
		printf("%d [%10s] %s(%p):",	i+1,
						m_patternArray[i]->m_forceFieldName,
					   	m_patternArray[i]->m_element,
						m_patternArray[i]	
					);
		
		std::list<AtomPattern *>::iterator it;
		for(	it=m_patternArray[i]->m_connectedTo.begin();
	  		it!=m_patternArray[i]->m_connectedTo.end();
			it++)
		{
			AtomPattern *x = *it;
			printf(" %s(%p)",x->m_element,x);
		}	
	printf("\n");

	}


}





void AtomPatternArray::toString(std::string *str)
{

	(*str)+=getPatternName();
	(*str)+=":\n";
	
	int i;
	for(i=0;i<m_N;i++)
	{ 
		m_patternArray[i]->allToString(str);
	}
	
	(*str)+='\n';

	for(i=0;i<m_N;i++)
	{
		if(m_patternArray[i]->m_forceFieldName[0]==0) continue;
		m_patternArray[i]->rootToString(str);
		(*str)+=" : ";
		(*str)+=m_patternArray[i]->m_forceFieldName;
		(*str)+='\n';
	}

}
