#ifndef ParametersAdaptor_h
#define ParametersAdaptor_h

#include "Object.h"
#include "Parameters.h"
#include "upperString.h"
#include "Exception.h"

#include "PairParameter.h"
#include "ArrayParameter.h"
#include <vector>

class ParametersAdaptor : public Object
{
protected:
	Parameters *m_parameters;
public:
	ParametersAdaptor(Parameters *params)
	{
		m_parameters = params;
	}

	Parameter *getTypedParameter(	const char *name,
					Integer Type);

	Real getDoubleParameter(const char *paramName)
	{
		return getTypedParameter(paramName,Parameter::DOUBLE)->getDouble();
	}

	const char *getStringParameter(const char *paramName)
	{
		return getTypedParameter(paramName,Parameter::STRING)->getStringPtr();
	}

	PairParameter *getPairParameter(const char *paramName)
	{
		return (PairParameter *)
		       getTypedParameter(paramName,Parameter::PAIR);
	}	

	std::vector<Parameter *> *getArrayParameter(const char *paramName)
	{
		return  ( (ArrayParameter*)
			getTypedParameter(paramName,Parameter::ARRAY) )
			->getData();
	}

	Parameters *getParameters()
	{
		return m_parameters;
	}

};



/* Real */
#define GET_DOUBLE_PARAMETER(paramName,GetName)	\
Real get##GetName() { return getDoubleParameter(paramName);}

#define GET_DOUBLE_PARAMETER_WITH_DEFAULT(paramName,GetName,Default)	\
Real get##GetName()							\
{ if(!m_parameters->hasParameter(paramName)) return Default;			\
  else return getDoubleParameter(paramName); 				\
}
/*Integer*/
#define GET_INT_PARAMETER(paramName,GetName) \
Integer get##GetName() {return (Integer)getDoubleParameter(paramName);}

#define GET_INT_PARAMETER_WITH_DEFAULT(paramName,GetName,Default)	\
Integer get##GetName()							\
{ if(!m_parameters->hasParameter(paramName)) return Default;			\
  else return (Integer)getDoubleParameter(paramName); 				\
}
/*string*/
#define GET_STRING_PARAMETER(paramName,GetName)	\
const char* get##GetName() { return getStringParameter(paramName);}

#define GET_STRING_PARAMETER_WITH_DEFAULT(paramName,GetName,Default)	\
const char *get##GetName()							\
{ if(!m_parameters->hasParameter(paramName)) return Default;			\
  else return getStringParameter(paramName); 				\
}

/*boolean*/
#define GET_BOOLEAN_PARAMETER(paramName,FunctionName)	\
Integer FunctionName()					\
{const char *Boolean = getStringParameter(paramName);	\
 char str[256];						\
 upperString(str,Boolean);				\
 if(	!strcmp(str,"T") ||                     \
	!strcmp(str,"TRUE") ||                  \
	!strcmp(str,"YES") || 			\
	!strcmp(str,"Y") || 			\
	!strcmp(str,"ON") ) return 1;		\
						\
 if(    !strcmp(str,"F")  ||                    \
	!strcmp(str,"FALSE") ||                 \
	!strcmp(str,"NO") || 			\
	!strcmp(str,"N") || 			\
	!strcmp(str,"OFF") ) return 0;		\
 sprintf(str,"invalid value of boolean parameter %s",paramName);\
 throw new Exception(this,str);				\
}

#define GET_BOOLEAN_PARAMETER_WITH_DEFAULT(paramName,FunctionName,Default) \
Integer FunctionName()					\
{ if(  !m_parameters->hasParameter(paramName)) return Default;\
const char *Boolean = getStringParameter(paramName);	\
 char str[256];						\
upperString(str,Boolean);				\
 if(    !strcmp(str,"T") ||                     \
	!strcmp(str,"TRUE") ||                  \
	!strcmp(str,"YES") || 			\
	!strcmp(str,"Y") || 			\
	!strcmp(str,"ON") ) return 1;		\
							\
 if(	!strcmp(str,"F") ||                             \
	!strcmp(str,"FALSE") ||                         \
          !strcmp(str,"NO") || 			\
	!strcmp(str,"N") || 			\
	!strcmp(str,"OFF") ) return 0;		\
 sprintf(str,"invalid value of boolean parameter %s",paramName);\
 throw new Exception(this,str);				\
}



/*case*/
#define BEGIN_CASE_PARAMETER(paramName,GetName,GetType)	\
GetType get##GetName()					\
{							\
	const char *val= getStringParameter(paramName);	\
	GetType result = (GetType)NULL;			\
	const char *name = paramName;	
	
#define CASE(paramValue,GetValue)			\
	if(!strcmp(val,paramValue)) result = GetValue;

#define END_CASE_PARAMETER						\
	if((long)result == 0)						\
	{	char Error[256];					\
		sprintf(Error,"invalid value %s of parameters %s",val,name);\
		throw new Exception(this,Error); 			\
	}								\
	return result;							\
}

/*example*/
/*


BEGIN_CASE_PARAMETER("closure",ClosureFactory,ClosureFactory3DRISM *)

CASE("HNC",m_HNCClosureFactory)
CASE("KH",m_PLHNCClosureFactory)

END_CASE_PARAMETER

*/

#endif
