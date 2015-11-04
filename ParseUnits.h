#ifndef ParseUnits_h
#define ParseUnits_h

#include "ParseStatement.h"

class ParseUnits : public ParseStatement
{
protected:
	const char *m_baseDistance;
	const char *m_baseEnergy;

	Integer m_distancePow,m_energyPow;
	Real m_distanceKoef,m_energyKoef;

public:
	ParseUnits(	const char *baseDistance,
		 	const char *baseEnergy)
	: ParseStatement("units")
	{
		m_baseDistance = baseDistance;
		m_baseEnergy = baseEnergy;
	}

	Integer getDistancePow()
	{
		return m_distancePow;	
	}
	
	Integer getEnergyPow()
	{
		return m_energyPow;
	}
	
	Real getDistanceKoef()
	{
		return m_distanceKoef;
	}

	Real getEnergyKoef()
	{
		return m_energyKoef;
	}

	Real getKoef()
	{
		return m_distanceKoef * m_energyKoef;
	}

	virtual Integer parse(StringParser *sp);

};


#endif
