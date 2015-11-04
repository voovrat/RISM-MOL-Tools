#include "ParseAtom.h"

#include "ParseName.h"
#include "ParseUnsigned.h"
#include "StringParser.h"

#include <string.h>

#include "AtomPattern.h"

void ParseAtom::getElement(char *dst,Integer N)
{
	strncpy(dst,m_element,N);
}


Integer ParseAtom::parse(StringParser *sp)
{
	ParseName parseName;
	ParseUnsigned parseUnsigned;


	if(! expectStatement(sp,&parseName)) return 0;

	parseName.getString(m_element,8);

	if(! expectChar(sp,'(')) return 0;

	if(!expectStatement(sp,&parseUnsigned)) return 0;

	m_label = parseUnsigned.getInteger();

	if(!expectChar(sp,')')) return 0;

	if(expectChar(sp,'T')) 
	{
		m_isTerminal = 1;
	}

	return 1;
}

void ParseAtom::toAtomPattern(AtomPattern *atomPattern)
{
	getElement(atomPattern->m_element,8);
	atomPattern->m_isTerminal = isTerminal();
	atomPattern->m_label = m_label;
}

/*
main()
{
const char *str="C(5)T";
char element[8];

ParseAtom pa;
StringParser sp(str);
int r;

r=pa.parse(&sp);

pa.getElement(element,8);

printf("%d : %s %d T%d\n",r,element,pa.getLabel(),pa.isTerminal());

}
*/
