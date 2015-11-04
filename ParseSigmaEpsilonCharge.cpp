#include "ParseSigmaEpsilonCharge.h"
#include "SigmaEpsilonCharge.h"

#include "ParseName.h"
#include "ParseDouble.h"
#include "StringParser.h"

#include "ParseNonSpace.h"

#include <string.h>

Integer ParseSigmaEpsilonCharge::parse(StringParser *sp)
{
ParseName parseName;
ParseDouble parseDouble;
ParseNonSpace parseNonSpace;

#define PARSE(parse) sp->skipChars(" \t"); if(!expectStatement(sp,&parse)) return 0;

#define PARSE_NAME(s,len) PARSE(parseName) parseName.getString(s,len);
#define PARSE_DOUBLE(x) PARSE(parseDouble) x=parseDouble.getDouble();
#define PARSE_NONSPACE(s,len) PARSE(parseNonSpace) strncpy(s,parseNonSpace.m_string,len);


PARSE_NAME(m_atomType,256)
//PARSE_NAME(m_bond_type,256)
PARSE_NONSPACE(m_bond_type,8)
PARSE_DOUBLE(m_atomicNumber)
PARSE_DOUBLE(m_mass)
PARSE_DOUBLE(m_charge)
PARSE_NAME(m_ptype,8)
PARSE_DOUBLE(m_sigma)
PARSE_DOUBLE(m_epsilon)

return 1;
}
