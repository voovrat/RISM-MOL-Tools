#ifndef ParseKeyValuePair_h
#define ParseKeyValuePair_h

#include "ParseStatement.h"
#include "Parameter.h"
#include "PairParameter.h"


//   syntax A:B where A,B - values
//   

class ParseKeyValuePair : public ParseStatement
{
protected:
	const char *m_distanceUnits;
	const char *m_energyUnits;

	PairParameter *m_pair;
	
public:
	ParseKeyValuePair(const char *distanceUnits,
		  const char *energyUnits)
	: ParseStatement("key-value pair")
	{
		m_pair = NULL;
		m_distanceUnits = distanceUnits;
		m_energyUnits = energyUnits;
	}

	virtual ~ParseKeyValuePair()
	{
		if(m_pair) NULL_DELETE(m_pair);
		m_pair = NULL;
	}

	PairParameter *retainPair()
	{
		return (PairParameter *)m_pair->retainCopy();
	}

	virtual Integer parse(StringParser *sp);
};

#endif
