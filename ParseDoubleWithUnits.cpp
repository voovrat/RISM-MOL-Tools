#include "ParseDoubleWithUnits.h"

#include "StringParser.h"
#include "ParseUnits.h"
#include "ParseDouble.h"


Integer ParseDoubleWithUnits::parse(StringParser *sp)
{
	ParseDouble real;
	ParseUnits units(m_distanceUnits,m_energyUnits);

	if(!expectStatement(sp,&real)) return 0;

	m_value = real.getDouble();
	
	sp->skipSpace();
	if(!expectStatement(sp,&units)) return 1;

	m_value *= units.getKoef();

	return 1;
}
