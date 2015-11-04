#include "ParseParameter.h"

#include <stdio.h>
#include <string.h>
#include "ParseName.h"
//#include "ParseString.h"
//#include "ParseDouble.h"
//#include "StringParameter.h"
//#include "PlainDoubleParameter.h"
//#include "ParseDoubleWithUnits.h"
#include "StringParser.h"
#include "ParseValue.h"

void ParseParameter::getParameterName(char *dst,Integer maxLen)
{
	strncpy(dst,m_string,maxLen);
}

Integer ParseParameter::parse(StringParser *sp)
{
	ParseName name;
	ParseValue value(m_distanceUnits,m_energyUnits);
//	ParseString string;
//	ParseDoubleWithUnits doubleWithUnits(m_distanceUnits,m_energyUnits);

	sp->skipSpace();
	if(!expectStatement(sp,&name)) return 0;

	name.getString(m_string,256);
	sp->skipSpace();
	if(!expectChar(sp,'=')) return 0;

	if(m_parameter) NULL_DELETE(m_parameter);
	m_parameter = NULL;

	
	
	sp->skipSpace();
	if(expectStatement(sp,&value))
	{
		m_parameter = value.retainValue();
	}
	else
		return 0;
/*	if(expectStatement(sp,&doubleWithUnits))
	{
		m_parameter = new PlainDoubleParameter(doubleWithUnits.getDouble());
	}
	else if(expectStatement(sp,&string))
	{
		char str[256];
		string.getString(str,256);

		m_parameter = new StringParameter(str);
	}
	else
	{
		fillExpected(sp,"Real or string");
		return 0;
	}
*/
	
	sp->skipSpace();
	if(!expectChar(sp,';')) return 0;
	
	return 1;
}
