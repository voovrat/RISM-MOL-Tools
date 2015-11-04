#include "Units.h"

#include "Constants.h"
#include "Exception.h"

Integer Units::hasUnits(const char *name)
{
	ITERATOR it = m_unitValues.find(name);
	return it!=m_unitValues.end();
}


Real Units::unit2unit(const char *u1,const char *u2)
{
	ITERATOR it = m_unitValues.find(u1);
	
	if(it==m_unitValues.end())
	{	char Error[256];
		sprintf(Error,"Units::unit2unit : unknown unit %s ",u1 );
		throw new Exception(this,Error);
	}

	Real u1m = (*it).second;

	it = m_unitValues.find(u2);

	if(it==m_unitValues.end())
	{	char Error[256];
		sprintf(Error,"Units::unit2unit : unknown unit %s ",u2 );
		throw new Exception(this,Error);
	}
	
	Real u2m = (*it).second;

	return u1m/u2m;
}

	//convert value form units u1 to units u2
Real Units::convertFromTo(Real x,const char *u1,const char *u2)
{
	return x*unit2unit(u1,u2);
}

class EnergyUnits : public Units
{

public:
	EnergyUnits() 
	{
		Real kB=BOLTZMANN_CONSTANT; //1.3806504e-23; // J/K
		Real Na= AVAGADRO_NUMBER; //6.02214179e23; // 1/mol
		Real Tn = NORMAL_TEMPERATURE; //298.15; // K, normal temperature

		m_unitValues["J"] = 1;
		m_unitValues["Hartree"] = 4.35974417e-18;
		m_unitValues["kcal/mol"] = 6.9477e-21;
		m_unitValues["KBT"] = Tn*kB;
		m_unitValues["kJ/mol"] = 1000/Na;
		m_unitValues["eV"] = 1.60217653e-19;
		m_unitValues["K"] = kB;
	}	
};


class DistanceUnits : public Units
{

public:
	DistanceUnits() 
	{
		m_unitValues["m"] = 1;
		m_unitValues["Angstr"] = 1e-10;
		m_unitValues["Bohr"] = 5.291772108e-11;
		m_unitValues["nm"] = 1e-9;
	}	
};

class ChargeUnits : public Units
{

public:

	ChargeUnits()
	{
		m_unitValues["C"] = 1;
		m_unitValues["e"] = 1.60217648740e-19;
	}

};


class VolumeUnits : public Units
{

protected:

	Real cube(Real x)
	{
		return x*x*x;
	}

public:
	VolumeUnits() 
	{
		m_unitValues["m3"] = 1;
		m_unitValues["Angstr3"] = cube(1e-10 );
		m_unitValues["Bohr3"] = cube(5.291772108e-11);
		m_unitValues["nm3"] = cube(1e-9);
	}	
};


Units *Units::m_distanceUnits = new DistanceUnits();
Units *Units::m_energyUnits = new EnergyUnits();
Units *Units::m_chargeUnits = new ChargeUnits();
Units *Units::m_volumeUnits = new VolumeUnits();
