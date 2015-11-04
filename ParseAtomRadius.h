#ifndef ParseAtomRadius_h
#define ParseAtomRadius_h

#include "Settings.h"
#include "ParseStatement.h"

// Parse the following statement: 
// element : sigma
// element is a string, sigma - real number (in angstroms)
// e.g.
//  C : 3.5
//  H : 0.4
//  O : 3.16

class ParseAtomRadius : public ParseStatement
{
public:
	char m_element[8];
	Real m_sigma;

public:
	ParseAtomRadius()
	: ParseStatement("atomRadius")
	{ 	m_element[0]=0;
		m_sigma=0;
	}

	virtual Integer parse(StringParser *sp);

};


#endif
