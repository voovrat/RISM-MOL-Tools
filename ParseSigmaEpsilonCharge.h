#ifndef ParseSigmaEpsilonCharge_h
#define ParseSigmaEpsilonCharge_h

// Parse a ffoplsaanb.itp gromacs file (non-bonded)
// the file cotain atom types, sigma, epsilon and charge parameters
// comment symbol in the file is ';'

// NOTE: preprocessor instructions are  NOT interpreted!!!
// NOTE: itp file should contain ONLY ONE section - [ atomtypes ] 

#include "ParseStatement.h"
#include "StringParser.h"

// Parse one record in [ atomtypes ] section of itp file.
// record contains:
// ; name     bond_type    mass    charge      ptype          sigma      epsilon
//   opls_001   C	    6      12.01100     0.500       A    3.75000e-01  4.39320e-01 

class ParseSigmaEpsilonCharge : public ParseStatement
{
public:
	char m_atomType[256];	
	char m_bond_type[8];
	Real m_atomicNumber;
	Real m_mass;
	Real m_charge;
	char m_ptype[8];
	Real m_sigma; 	// nm
	Real m_epsilon; // kJ/mol

public:
	ParseSigmaEpsilonCharge()
		: ParseStatement("sigmeEpsilonCharge")
	{
	}

	virtual Integer parse(StringParser *sp);

};


#endif
