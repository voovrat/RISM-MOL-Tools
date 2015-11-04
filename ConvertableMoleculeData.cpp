#include "ConvertableMoleculeData.h"

#include <stdlib.h>

template<class T>
void ConvertableMoleculeData<T>::cleanUp()
{
	 MoleculeData::cleanUp();	
	if(m_convertedRawData)
	{
		free(m_convertedRawData);
		m_convertedRawData = NULL;
	}
}

template<class T>
void ConvertableMoleculeData<T>::allocData(Integer NLin)
{
	MoleculeData::allocData(NLin);

	m_convertedRawData = (T *)malloc(NLin * m_ncol * sizeof(T));
}


template<class T>
void ConvertableMoleculeData<T>::convertData()
{
	Real *src;
	T *dst;	

	

	Integer i;

	src = m_rawData;
	dst = m_convertedRawData;
	for(i=0;i<m_N;i++,src++,dst++)
	{
		*dst = (T)*src;
	}
}


