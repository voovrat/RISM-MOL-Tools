#ifndef ParseAtom_h
#define ParseAtom_h

#include "ParseStatement.h"

class AtomPattern;

//  Element(index)T
// T - optional, means "Terminal"

class ParseAtom : public ParseStatement
{
protected:
	char m_element[8];
	int m_label;
	int m_isTerminal;

public:
	ParseAtom()
	: ParseStatement("atom")
	{ 	m_element[0]=0;
		m_label=-1;
		m_isTerminal=0; 
	}

	void getElement(char *str,Integer maxLen);
	const char *getElement()
	{
		return m_element;
	}

	int getLabel()
	{
		return m_label;
	}
	int isTerminal()
	{
		return m_isTerminal;
	}

	virtual Integer parse(StringParser *sp);

	void toAtomPattern(AtomPattern *atomPattern);


};


#endif
