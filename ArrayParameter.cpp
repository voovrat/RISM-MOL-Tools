#include <stdio.h>
#include "ArrayParameter.h"
#include <vector>

using namespace std;

Parameter *ArrayParameter::clone()
{
	ArrayParameter *p = new ArrayParameter();
 	p->getData()->reserve( this->m_data.size() );

	vector<Parameter *>::iterator it;
	for( it=m_data.begin(); it!=m_data.end(); it++)
	{
		p->getData()->push_back( (*it)->clone() );
	}
	return p;
}

Parameter *ArrayParameter::retainCopy()
{
	this->retain();
	vector<Parameter *>::iterator it;
	for( it=m_data.begin(); it!=m_data.end(); it++)
	{
		(*it)->retainCopy();
	}
	return this;
}

std::string ArrayParameter::toString()
{
	std::string s;
	s+='{';
	std::vector<Parameter *>::iterator it;
	for(it=m_data.begin(); it!=m_data.end(); it++)
	{
		s+=(*it)->toString();
		if( (it+1) != m_data.end())
			s+=",\n";
		else
			s+="}\n";
	}
	return s;
}
