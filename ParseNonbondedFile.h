#ifndef ParseNonbondedFile_h
#define ParseNonbondedFile_h

// Parse a ffoplsaanb.itp gromacs file (non-bonded)
// the file cotain atom types, sigma, epsilon and charge parameters
// comment symbol in the file is ';'

// NOTE: preprocessor instructions are  NOT interpreted!!!
// NOTE: itp file should contain ONLY ONE section - [ atomtypes ] 

#include "ParseStatement.h"
#include "StringParser.h"

#include "SigmaEpsilonCharge.h"

#include <string>
#include <map>

class ParseNonbondedFile : public ParseStatement
{
protected:
	std::map<std::string,SigmaEpsilonCharge > *m_ff; // is an input parameter							//will be filled during the parsing


public:
	ParseNonbondedFile( std::map<std::string,SigmaEpsilonCharge > *ff 
			  )
		: ParseStatement("parseNonbondedFile")
	{
		m_ff = ff;
	}


	virtual Integer parse(StringParser *sp);
};


#endif
