#include "ParametersAdaptor.h"


Parameter *ParametersAdaptor::getTypedParameter(
				const char *paramName,
				Integer Type)
{	char Error[256];
	if(!m_parameters->hasParameter(paramName))
	{	sprintf(Error,"parameter %s was not defined",paramName);
		throw new Exception(this,Error);
	}
	Parameter *p=m_parameters->getParameter(paramName);

	if(p->getType()!=Type)
	{
		sprintf(Error," invalid type of parameter %s",paramName);
		throw new Exception(this,Error);
	}		
	return p;
}


