#ifndef ConvertableMoleculeData_h
#define ConvertableMoleculeData_h

#include "MoleculeData.h"

template<class T>
class ConvertableMoleculeData : public MoleculeData
{
protected:

// inherited	Real *m_rawData;

// inherited	Integer m_N;
// inherited	Integer m_ncol;

T *m_convertedRawData;

public:
	ConvertableMoleculeData(Integer ncol)
	: MoleculeData(ncol)
	{
		m_convertedRawData=NULL;
	} 

	virtual Real *getDoubleData()
	{
		return m_rawData;
	}

	virtual void cleanUp();
	virtual void allocData(Integer NLin);

	virtual void convertData();
};

#endif
