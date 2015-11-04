#ifndef ParseValue_h
#define ParseValue_h

#include "ParseStatement.h"
#include "Parameter.h"

#include <map>
#include <string>

class ParseValue : public ParseStatement
{
protected:
	const char *m_distanceUnits;
	const char *m_energyUnits;

	Parameter *m_value;
	
public:
	ParseValue(	const char *distanceUnits,
			const char *energyUnits)
	: ParseStatement("value")
	{
		m_value = NULL;
		m_distanceUnits = distanceUnits;
		m_energyUnits = energyUnits;
	}

	virtual ~ParseValue()
	{
		if(m_value) NULL_DELETE(m_value);
		m_value = NULL;
	}

	Parameter *getValueCopy()
	{
		return m_value->clone();
	}

        Parameter *retainValue()
	{
          	m_value->retain();
		return m_value;
        }

	virtual Integer parse(StringParser *sp);
};

#endif
