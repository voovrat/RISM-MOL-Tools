#include "ParseValue.h"

#include <stdio.h>
#include <string.h>
#include "ParseName.h"
#include "ParseString.h"
#include "ParseDouble.h"
#include "StringParameter.h"
#include "PlainDoubleParameter.h"
#include "ParseDoubleWithUnits.h"
#include "ParsePair.h"
#include "ParseArray.h"
#include "StringParser.h"



Integer ParseValue::parse(StringParser *sp)
{
	ParseString string;
	ParseDoubleWithUnits doubleWithUnits(m_distanceUnits,m_energyUnits);
	ParsePair pair(m_distanceUnits,m_energyUnits);
	ParseArray array(m_distanceUnits,m_energyUnits);

	if(m_value) NULL_DELETE(m_value);

	sp->skipSpace();
	if(expectStatement(sp,&doubleWithUnits))
	{
		m_value = new PlainDoubleParameter(doubleWithUnits.getDouble());
	}
	else if(expectStatement(sp,&string))
	{
		char str[256];
		string.getString(str,256);

		m_value = new StringParameter(str);
	}
	else if(expectStatement(sp,&pair))
	{
		m_value = pair.retainPair(); 	
	}
	else if(expectStatement(sp,&array))
	{
		m_value = array.retainArray();
	}
	else
	{
		fillExpected(sp,"Real or string");
		return 0;
	}

	return 1;
}
