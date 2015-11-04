#include "ParseLoad.h"

#include <string.h>
#include "loadParametersFile.h"
#include "ParseName.h"
#include "ParseString.h"
#include "StringParser.h"

Integer ParseLoad::parse(StringParser *sp)
{	char str[256];
	ParseName name;
	ParseString string;

	sp->skipSpace();

	if(!expectStatement(sp,&name)) return 0;

	name.getString(str,256);
	
	if(strcmp(str,"load")!=0) return 0;

	sp->skipSpace();

	if(!expectChar(sp,'(')) return 0;
	sp->skipSpace();

	if(!expectStatement(sp,&string)) return 0;

	sp->skipSpace();
	if(!expectChar(sp,')')) return 0;
	sp->skipSpace();

	if(!expectChar(sp,';')) return 0;
	
	string.getString(str,256);

	loadParametersFile(	str,	//const char *fname,
				m_parameters,//	Parameters *parameters
				m_distanceUnits,
				m_energyUnits
			);

	return 1;

}
