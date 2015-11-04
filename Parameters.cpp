#include "Parameters.h"
#include "Pointer.h"

#include "PlainDoubleParameter.h"
#include <stdlib.h>
#include <stdio.h>

Parameters::Parameters()
{
}


Integer Parameters::hasParameter(const char *name)
{
	char upperName[256];
	upperString(upperName,name);
	return m_map.find(upperName) != m_map.end();
}
	
Parameter *Parameters::getParameter(const char *name)
{
	char upperName[256];
	upperString(upperName,name);

	if(!hasParameter(upperName)) return NULL;
		return m_map[upperName];
}

void Parameters::setParameter(const char *name, Parameter *p)
{
	char *upperName=(char*)malloc(strlen(name)+1);
	char s[256];	

	upperString(upperName,name);
//	p->toString(s);
//	printf("setParameter : [%s]=[%s]\n",upperName,s);
	m_text += name;
	m_text += '=';
	m_text += p->toString();
	m_text += ";\n";

	Parameter *pclone = p->clone();
	m_map[upperName] = pclone;
	addToDeleteList(pclone);
	addToDeleteList(new Pointer(upperName));
}

const char *Parameters::toString()
{
//	char str[256];

	m_text.clear();
	std::map<std::string,Parameter *>::iterator it;
	for(it=m_map.begin(); it!=m_map.end(); it++)
	{
		m_text += (*it).first;
		m_text += " = ";
                m_text += (*it).second->toString();
//		(*it).second->toString(str);
//		if( (*it).second->getType()==Parameter::STRING )
//		{
//			m_text += "\"";
//			m_text += str;
//			m_text += "\"";
//		}
//		else
//			m_text += str;
		m_text += ";\n";
		
	}

	return m_text.c_str();	
}
