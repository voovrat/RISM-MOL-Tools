#ifndef MoleculeData_h
#define MoleculeData_h

#include "Object.h"

class MoleculeData : public Object
{
protected:

	Real *m_rawData;

	Integer m_N;
	Integer m_ncol;

public:
	MoleculeData(Integer ncol)
	{
		m_ncol = ncol;
		m_N = 0;
		m_rawData=NULL;
	} 

	virtual ~MoleculeData();

	virtual void cleanUp();
	virtual void allocData(Integer NLin);


	Integer getNumSites()
	{
		return m_N;
	}

	Real *getRawData()
	{
		return m_rawData;
	}
};

#endif
