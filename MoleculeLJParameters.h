#ifndef MoleculeLJParameters_h
#define MoleculeLJParameters_h

#include "MoleculeData.h"

class MoleculeLJParameters : public MoleculeData
{
public:
	MoleculeLJParameters() 
	: MoleculeData(2)
	{}

	Real *getSigma()
	{
		return m_rawData;
	}
		
	Real *getEpsilon()
	{
		return m_rawData+m_N;
	}

};


#endif
