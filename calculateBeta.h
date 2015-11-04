#ifndef calculateBeta_h
#define calculateBeta_h

#include "Units.h"

inline Real calculateBeta(Real T) // returns beta in Hartree
{
	Real Kb = Units::energyUnits()->unit2unit("K","Hartree");
	return 1/Kb/T;
}

#endif
