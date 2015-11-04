#ifndef MoleculeCoordinates_h
#define MoleculeCoordinates_h

#include "MoleculeData.h"


class MoleculeCoordinates : public MoleculeData
{
public:
	MoleculeCoordinates() 
	: MoleculeData(3)
	{}

	Real *getX()
	{
		return m_rawData;
	}

	Real *getY()
	{
		return m_rawData+m_N;
	}
	
	Real *getZ()
	{
		return m_rawData+2*m_N;
	}

};

#endif


