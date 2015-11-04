#ifndef GridComparator1DRISM_h
#define GridComparator1DRISM_h

#include "Comparator.h"
#include "Grid1DRISM.h"


class GridComparator1DRISM : public Comparator<Grid>
{
protected:
	GridComparator1DRISM() {}

public:
	static GridComparator1DRISM *getInstance();

	virtual bool isLess(const Grid *a,const Grid *b);
};


#endif
