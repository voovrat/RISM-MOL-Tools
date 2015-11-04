#include "VerboseNorm.h"

#include <stdio.h>
#include "TextLog.h"

Real VerboseNorm:: calculateNorm(Object *x,Object *y)
{
	Real norm = m_subNorm->calculateNorm(x,y);
	
	TextLog *log = TextLog::getInstance();

	char s[1024];
	sprintf(s,"%s%le%s",m_prefix,norm,m_suffix);
	log->printString(m_verbosity,s);

	return norm;
}
