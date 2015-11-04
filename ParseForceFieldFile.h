#ifndef ParseForceFieldFile_h
#define ParseForceFieldFile_h

#include "ParseNonbondedFile.h"
#include "ParsePatternFile.h"

#include "ParseStatement.h"
#include "StringParser.h"

#include "SigmaEpsilonCharge.h"

#include <string>
#include <map>


class ParseForceFieldFile : public ParseStatement 
{
protected:
	ParseNonbondedFile m_parseNonbonded;
	ParsePatternFile m_parsePatternFile;

public:

ParseForceFieldFile( 	std::map<std::string,SigmaEpsilonCharge > *ff,
 			std::list<AtomPatternArray *> *patterns
 )
: m_parseNonbonded(ff), m_parsePatternFile(patterns),
 ParseStatement("forcefieldfile")
{}

virtual Integer parse(StringParser *sp)
{
	if(!expectStatement(sp,&m_parsePatternFile)) return 0;
	if(!expectStatement(sp,&m_parseNonbonded)) return 0;

	return 1; 
}

ParseNonbondedFile *getParseNonbondedFile()
{
	return &m_parseNonbonded;
}

ParsePatternFile *getParsePatternFile()
{
	return &m_parsePatternFile;
}



};



#endif
