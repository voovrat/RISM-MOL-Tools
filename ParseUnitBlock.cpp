#include "ParseUnitBlock.h"

#include <string.h>
#include "StringParser.h"
#include "ParseName.h"
#include "ParseInteger.h"

void ParseUnitBlock::getUnitName(char *dst,Integer maxLen)
{
	strncpy(dst,m_unitName,maxLen);
}


Integer ParseUnitBlock::parse(StringParser *sp)
{
	ParseName name;
	ParseInteger integer;

	if(!expectStatement(sp,&name)) return 0;

	name.getString(m_unitName,256);
	m_power=1;

	if(!expectChar(sp,'^')) return 1;

	if(!expectStatement(sp,&integer)) return 0;

	m_power = (Integer)integer.getInteger();

	return 1;
}
