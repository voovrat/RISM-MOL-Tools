#include "StringParameter.h"

#include <stdlib.h>
#include <string.h>

std::string StringParameter::slashify(const char *s)
{
	std::string str;
	for(;*s;s++)
	{
		if(*s == '\'' || *s == '\"' || *s=='\\' ) str += '\\';
		str += *s;
	}

	return str;
}

StringParameter::StringParameter(const char *string)
{
	m_string = (char *)malloc(strlen(string)+1);
	strcpy(m_string,string);
}

StringParameter::~StringParameter()
{
	if(m_string) free(m_string);
	m_string = NULL;
}

void StringParameter::getString(char *dst,Integer maxLen)
{
	strncpy(dst,m_string,maxLen);
}

