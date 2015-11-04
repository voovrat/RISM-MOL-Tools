#ifndef BinaryOperation_h
#define BinaryOperation_h

#include "Settings.h"
#include "Object.h"

template<class T>
class BinaryOperation : public Object
{
public:
	virtual	void operator()(T src,T dst)=0;
};


#endif
