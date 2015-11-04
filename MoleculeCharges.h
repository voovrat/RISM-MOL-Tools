#ifndef MoleculeCharges_h
#define MoleculeCharges_h

#include "MoleculeData.h"

class MoleculeCharges : public MoleculeData
{
public:
	MoleculeCharges() 
	: MoleculeData(1)
	{}

	Real *getCharge()
	{
		return m_rawData;
	}

};


#endif
