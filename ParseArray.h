#ifndef ParseArray_h
#define ParseArray_h

#include "ParseStatement.h"
#include "Parameter.h"
#include "ArrayParameter.h"

//  syntax:  {A  ,B, C, ... } where A,B,C - values OR key-value pairs 
//   i.e this is ok:
//           { A:1 , B, C:2, d, (3,4) : (2,5) , {1,2,3} } 

class ParseArray : public ParseStatement
{
protected:
	const char *m_distanceUnits;
	const char *m_energyUnits;

	ArrayParameter *m_array;
	
public:
	ParseArray(const char *distanceUnits,
		  const char *energyUnits)
	: ParseStatement("array")
	{
		m_array = NULL;
		m_distanceUnits = distanceUnits;
		m_energyUnits = energyUnits;
	}

	virtual ~ParseArray()
	{
		if(m_array) NULL_DELETE(m_array);
		m_array = NULL;
	}

	ArrayParameter *retainArray()
	{
		return (ArrayParameter *)m_array->retainCopy();
	}

	virtual Integer parse(StringParser *sp);
};

#endif
