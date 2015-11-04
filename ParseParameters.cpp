#include "ParseParameters.h"

#include "Parameter.h"
#include "ParseParameter.h"
#include "ParseComment.h"
#include "StringParser.h"
#include "Parameters.h"
#include "ParseLoad.h"


Integer ParseParameters::parse(StringParser *sp)
{
	ParseComment comment;
	ParseParameter parameter(m_distanceUnits,m_energyUnits);
	ParseLoad 	load(	m_distanceUnits,//const char *distanceUnits,
				m_energyUnits,//const char *energyUnits,
				m_parameters //Parameters *parameters
			);
 
	char name[256];
	Parameter *p;

	while(!sp->isOver())
	{	sp->skipSpace();
		if(sp->isOver()) break;

		if(expectStatement(sp,&comment)) continue;
		if(expectStatement(sp,&parameter)) 
		{
		parameter.getParameterName(name,256);
		p = parameter.getParameter();

		m_parameters->setParameter(name, p);
		NULL_DELETE(p);
		continue;
		}

		if(expectStatement(sp,&load)) continue;
		
		//fillExpected(sp,"parameter or comment or load statement");
		return 0;
	}
	return 1;
}
