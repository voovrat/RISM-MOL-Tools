#ifndef ParseSolventComponent_h
#define ParseSolventComponent_h

#include "ParseStatement.h"

// parses the following:
//  solvent.xyz   solvent.ff  concentation
// concentration is given in particles/ nm^3

class ParseSolventComponent : public ParseStatement 
{
public:
	char m_solventFile[256];
	char m_forceFieldFile[256];
	Real m_density;

public:
	ParseSolventComponent()	: ParseStatement("solventComponent")
	{
		m_solventFile[0]=0; 
		m_forceFieldFile[0]=0;
		m_density=0;
	}

	
	virtual Integer parse ( StringParser *sp);

};

#endif
