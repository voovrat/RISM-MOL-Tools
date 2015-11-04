#ifndef SiteMultiplicities_h
#define SiteMultiplicities_h

#include "ConvertableMoleculeData.h"

class SiteMultiplicities : public ConvertableMoleculeData<Integer>
{
public:
	SiteMultiplicities() 
	: ConvertableMoleculeData<Integer>(1)
	{}

	Integer *getSiteMultiplicities()
	{
		return m_convertedRawData;
	}


};


#endif
