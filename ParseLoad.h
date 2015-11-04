#ifndef ParseLoad_h
#define ParseLoad_h

#include "ParseStatement.h"

class Parameters;

class ParseLoad : public ParseStatement
{
protected:
	Parameters *m_parameters;
	const char *m_distanceUnits;
	const char *m_energyUnits;
public:
	ParseLoad(	const char *distanceUnits,
			const char *energyUnits,
			Parameters *parameters) 
	: ParseStatement("load")
	{	m_parameters = parameters;
		m_distanceUnits = distanceUnits;
		m_energyUnits = energyUnits;
	}

	virtual Integer parse(StringParser *sp);
	

};

#endif
