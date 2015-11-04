#ifndef Comparator_h
#define Comparator_h

#include "Object.h"

template<class T>
class Comparator : public Object
{
public:
	virtual bool isLess(const T *,const T *)=0;

	
	virtual bool isGreater(const T *x,const T *y)
	{
		return isLess(y,x);
	}

	virtual bool isEqual(const T *x, const T *y)
	{
		return !isLess(x,y) && !isLess(y,x);
	}
	
	virtual bool isNotEqual(const T *x,const T *y)
	{
		return isLess(x,y) || isLess(y,x);
	}

	virtual bool isNotLess(const T *x,const  T *y)
	{
		return ~isLess(x,y);
	}

	virtual bool isNotGreater(const T *x,const T *y)
	{
		return ~isGreater(x,y);
	}
	
};


#endif
