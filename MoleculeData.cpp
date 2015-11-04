#include "MoleculeData.h"

#include <stdlib.h>

MoleculeData::~MoleculeData()
{
	cleanUp();
}

void MoleculeData::cleanUp()
{
	if(m_N)
	{
		free(m_rawData);
		m_rawData=NULL;
	}
	m_N =0;
}

void MoleculeData::allocData(Integer NLin)
{
	cleanUp();

	m_rawData = (Real *)malloc( NLin * m_ncol * sizeof(Real));

	m_N = NLin;

}

