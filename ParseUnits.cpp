#include "ParseUnits.h"

#include "StringParser.h"
#include "Units.h"
#include "ParseUnitBlock.h"
#include <math.h>


Integer ParseUnits::parse(StringParser *sp)
{
	ParseUnitBlock unitBlock;
	char unitName[256];
	Integer power;

	Units *units;

	sp->skipSpace();
	if(!expectChar(sp,'[')) return 0;

	m_distanceKoef = 1;
	m_energyKoef = 1;

	do{	
		sp->skipSpace();
		if(expectChar(sp,']')) break;
		if(!expectStatement(sp,&unitBlock)) return 0;

		unitBlock.getUnitName(unitName,256);
		power = unitBlock.getPower();

		if(Units::distanceUnits()->hasUnits(unitName)) 
		{
			Real kDistance = Units::distanceUnits()->unit2unit(unitName,m_baseDistance);
			m_distanceKoef *= pow( (double)kDistance , (int)power);
	
		}
		else	
		if(Units::energyUnits()->hasUnits(unitName)) 
		{
			Real kEnergy = Units::energyUnits()->unit2unit(unitName,m_baseEnergy);
			m_energyKoef *= pow( (double)kEnergy ,(int) power);
		}		
		else
		{	char Error[256];
			sprintf(Error,"unknown unit: \'%s\'",unitName);
			fillExpected(sp,Error,"");
			return 0;
		}

	}while(1);
	
	return 1;
}
