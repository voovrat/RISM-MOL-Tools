#ifndef GridComparator3DRISM_h
#define GridComparator3DRISM_h

#include "Comparator.h"
#include "Grid3DRISM.h"


class GridComparator3DRISM : public Comparator<Grid>
{
protected:
	GridComparator3DRISM() {}

public:
	static GridComparator3DRISM *getInstance();

	virtual bool isLess(const Grid *a,const Grid *b);
};


#endif
