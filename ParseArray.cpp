#include "ParseArray.h"

#include <stdio.h>
#include <string.h>
#include "StringParser.h"
#include "ParseValue.h"
#include "ParseKeyValuePair.h"

#include <vector>

Integer ParseArray::parse(StringParser *sp)
{
	ParseValue value(m_distanceUnits,m_energyUnits);
	ParseKeyValuePair keyValue(m_distanceUnits, m_energyUnits);

	sp->skipSpace();
	if(!expectChar(sp,'{')) return 0;

	if(m_array) NULL_DELETE(m_array)
	m_array = new ArrayParameter();
	std::vector<Parameter *> *data = m_array->getData();

	while(1) 
	{
		sp->skipSpace();
		if(expectChar(sp,'}')) return 1;
				
		if(expectStatement(sp,&keyValue))
			data->push_back(keyValue.retainPair() );
		else if(expectStatement(sp,&value))
			data->push_back(value.retainValue());
		else
		{  
			fillExpected(sp,"VALUE or KEY VALUE PAIR");
			return 0;
		}

		sp->skipSpace();
		if(expectChar(sp,'}')) return 1;
		if(!expectChar(sp,',')) return 0;
	}

}
