#ifndef ParseParameters_h
#define ParseParameters_h

#include "ParseStatement.h"
#include <map>
#include <string>

class Parameter;
class StringParser;
class Parameters;

class ParseParameters : public ParseStatement
{
protected:
	const char *m_distanceUnits;
	const char *m_energyUnits;

	Parameters *m_parameters;

public:
	ParseParameters(	const char *distanceUnits,
				const char * energyUnits,
				Parameters *parameters
			)
	: ParseStatement("parameter list")
	{
		m_distanceUnits = distanceUnits;
		m_energyUnits = energyUnits;
		m_parameters = parameters;
	}
	
	virtual Integer parse(StringParser *sp);
};

#endif
