#ifndef Parameters_h
#define Parameters_h

#include <string>
#include <map>

#include "Parameter.h"
#include "upperString.h"

#include "PlainDoubleParameter.h"

class Parameters : public Object
{
protected:
	std::string m_text;
public:
	std::map<std::string,Parameter *> m_map;

	Parameters();

	virtual Integer hasParameter(const char *name);

	virtual Parameter *getParameter(const char *name);

	virtual void setParameter(const char *name, Parameter *p);

	virtual const char *toString();
};



#endif
