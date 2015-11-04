#ifndef ParseUnitBlock_h
#define ParseUnitBlock_h

#include "ParseStatement.h"

class ParseUnitBlock : public ParseStatement
{
protected:
	char m_unitName[256];
	Integer m_power;
public:

	ParseUnitBlock()
	: ParseStatement("unit block")
	{
		m_unitName[0]=0;
		m_power =0;
	}

	void getUnitName(char *dst,Integer maxLen);
	Integer getPower()
	{
		return m_power;
	}
	
	virtual Integer parse(StringParser *sp);

};


#endif
