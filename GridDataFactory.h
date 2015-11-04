#ifndef GridDataFactory_h
#define GridDataFactory_h

#include "Object.h"

class Grid;

class GridDataFactory : public Object
{
public:
	virtual Object *createData(Grid *grid)=0;
};


#endif
