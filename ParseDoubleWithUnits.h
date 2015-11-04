#ifndef ParseDoubleWithUnits_h
#define ParseDoubleWithUnits_h

#include "ParseStatement.h"

class ParseDoubleWithUnits : public ParseStatement 
{
protected:
	const char *m_distanceUnits;
	const char *m_energyUnits;

	Real m_value;

public:

	ParseDoubleWithUnits(	const char *distanceUnits,
				const char *energyUnits)
	: ParseStatement("number with units")
	{
		m_distanceUnits = distanceUnits;
		m_energyUnits = energyUnits;
	}

	Real getDouble()
	{
		return m_value;
	}

	virtual Integer parse(StringParser *sp);
};


#endif
