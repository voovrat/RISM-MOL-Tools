#ifndef Units_h
#define Units_h

#include <map>
#include <string>

#include "Object.h"

class Units : public Object
{
protected:

	typedef std::map<std::string,Real> MAP;
	typedef std::map<std::string,Real>::iterator ITERATOR;

	MAP m_unitValues;

	Units() {}

	static Units *m_energyUnits;
	static Units *m_distanceUnits;
	static Units *m_chargeUnits;
	static Units *m_volumeUnits;
	
public:
		

	static Units *energyUnits()
	{
		return m_energyUnits;
	}	

	static Units *distanceUnits()
	{
		return m_distanceUnits;
	}

	static Units *chargeUnits()
	{
		return m_chargeUnits;
	}
	
	static Units *volumeUnits()
	{
		return m_volumeUnits;
	}

	Integer hasUnits(const char *name);	

	//return conversion koefficient from u1 to u2
	Real unit2unit(const char *u1,const char *u2);

	//convert value form units u1 to units u2
	Real convertFromTo(Real x,const char *u1,const char *u2);
};


#endif
