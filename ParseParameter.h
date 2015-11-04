#ifndef ParseParameter_h
#define ParseParameter_h

#include "ParseStatement.h"
#include "Parameter.h"

#include <map>
#include <string>

class ParseParameter : public ParseStatement
{
protected:
	const char *m_distanceUnits;
	const char *m_energyUnits;

	Parameter *m_parameter;
	char m_string[256];
	
public:
	ParseParameter(	const char *distanceUnits,
			const char *energyUnits)
	: ParseStatement("parameter")
	{
		m_parameter = NULL;
		m_distanceUnits = distanceUnits;
		m_energyUnits = energyUnits;
	}

	virtual ~ParseParameter()
	{
		if(m_parameter) NULL_DELETE(m_parameter);
		m_parameter = NULL;
	}

	Parameter *getParameter()
	{
		return m_parameter->retainCopy();
	}

	void getParameterName(char *dst,Integer maxLen);

	virtual Integer parse(StringParser *sp);
};

#endif
