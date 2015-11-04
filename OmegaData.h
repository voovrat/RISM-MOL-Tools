#ifndef OmegaData_h
#define OmegaData_h

#include "MoleculeData.h"


class OmegaData : public MoleculeData
{
public:
	OmegaData() 
	: MoleculeData(3)
	{}

	Integer getNumOmega()
	{
		return getNumSites();
	}

	Integer getOmegaID(Integer i)
	{
		return (Integer)(*(m_rawData+i)+0.5);
	}

	Real *getOmegaCoeff()
	{
		return m_rawData+m_N;
	}
	
	Real *getOmegaPosition()
	{
		return m_rawData+2*m_N;
	}

};

#endif
