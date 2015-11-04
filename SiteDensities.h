#ifndef SiteDensities_h
#define SiteDensities_h

#include "MoleculeData.h"

class SiteDensities : public MoleculeData
{
public:
	SiteDensities() 
	: MoleculeData(1)
	{}

	Real *getDensity()
	{
		return m_rawData;
	}

};


#endif
