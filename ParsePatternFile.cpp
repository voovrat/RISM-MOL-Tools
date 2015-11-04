#include "ParsePatternFile.h"

#include "AtomPattern.h"
#include "ParseAtomPattern.h"

// ParseAtomPatterns, convert them to vectors and push_back to the m_patterns
void ParsePatternFile::elaborateStatement(ParseStatement *parseStatement)
{
// do not retain parseStatement -> it will be deleted
ParseAtomPattern *parseAtomPattern = (ParseAtomPattern *)parseStatement;
AtomPatternArray *patternArray = new AtomPatternArray();

parseAtomPattern->toAtomPatternArray(patternArray);

m_patterns->push_back(patternArray);
}


