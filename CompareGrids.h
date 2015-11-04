#ifndef CompareGrids_h
#define CompareGrids_h

#include "Object.h"

class Grid;

class CompareGrids : public Object
{
	virtual bool isLess(Grid *,Grid *)=0;
};


#endif
