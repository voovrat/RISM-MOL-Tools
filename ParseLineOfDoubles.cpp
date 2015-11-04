#include "Settings.h"

#include "ParseLineOfDoubles.h"

#include "ParseComment.h"
#include "ParseDouble.h"

Integer ParseLineOfDoubles::parse(StringParser *sp)
{
	ParseComment parseComment;
	ParseDouble parseDouble;
//	while(expectChars(sp," \t")) ;
	
	while(1)
	{


		sp->skipChars(" \t");


		if(expectStatement(sp,&parseComment) || expectChar(sp,'\n'))
		{
			return 1;
		}
		if(!expectStatement(sp,&parseDouble))
		{
			return 0;
		}

		double val = parseDouble.getDouble();

		m_line->push_back(val);
	
	}

}

