#include "ParseForceFieldName.h"

#include "StringParser.h"
#include "ParseName.h"

Integer ParseForceFieldName::parse(StringParser *sp)
{
	ParseName parseName;

	sp->skipChars(" \t");
	if(!expectStatement(sp,&m_parseAtom)) return 0;

	sp->skipChars(" \t");
	if(!expectChar(sp,':')) return 0;
	sp->skipChars(" \t");	

	if(!expectStatement(sp,&parseName)) return 0;
	
	parseName.getString(m_forceFieldName,256);
	
	return 1;

}
