#include "PairParameter.h"
#include <stdio.h>

/*
PairParameter()::PairParameter()
{
	m_first = NULL;
	m_second = NULL;
}

PairParameter::~PairParameter()
{

}
*/

Parameter *PairParameter::clone()
{
	PairParameter *p = new PairParameter();
 	p->m_first = m_first->clone();
	p->m_second = m_second->clone();
	return p;
}

/*void PairParameter::toString(char *s)
{
	char s1[256],s2[256];
	m_first->toString(s1);
	m_second->toString(s2);
	sprintf(s,"(%s,%s)",s1,s2);
}*/
