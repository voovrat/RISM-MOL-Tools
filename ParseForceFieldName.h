#ifndef ParseForceFieldName_h
#define ParseForceFieldName_h

#include "Settings.h"

#include "ParseStatement.h"
#include "ParseAtom.h"

//
// Parse The folowing construction
// Element(index) : name_in_force_field
//
// e.g   
//  C(1) : methyl_C

class ParseForceFieldName : public ParseStatement
{
public:
	ParseAtom m_parseAtom;
	char m_forceFieldName[256];

	ParseForceFieldName() : ParseStatement("forceFieldName")
	{
		m_forceFieldName[0]=0;
	}

	virtual Integer parse(StringParser *sp);
};



#endif


