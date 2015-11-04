#include "ParseWord.h"
#include "StringParser.h"
#include "string.h"

Integer ParseWord::parse(StringParser *sp)
{

sp->skipChars(m_delimiters);

int n;
for(n=0;n<255;n++)
{
	if(sp->currentCharIs(m_delimiters)) break;
	m_string[n] = sp->getChar();
}
m_string[n]=0;

return 1;
}

void ParseWord::getString(char *s,int N)
{
	strncpy(	s,	//char *dest, 
			m_string,//const char *src, 
			N	//size_t n
		);
}
