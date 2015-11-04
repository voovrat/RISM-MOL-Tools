#ifndef UnaryFunction_h
#define UnaryFunction_h

#include "Object.h"

template<class ArgumentType,class ResultType>
class UnaryFunction : public Object
{
public:
	virtual ResultType operator()(ArgumentType arg)=0;
};

#endif
