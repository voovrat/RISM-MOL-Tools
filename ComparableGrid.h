#ifndef ComparableGrid_h
#define ComparableGrid_h

#include "Object.h"
class Grid;
#include "Comparator.h"

class ComparableGrid : public Object
{
protected:
	Grid *m_grid;
	Comparator<Grid> *m_comparator;

public:
	
	ComparableGrid(	Grid *grid,
	    		Comparator<Grid> *comparator);

	ComparableGrid(const ComparableGrid &x)
	{
		m_grid=x.m_grid;
		m_comparator = x.m_comparator;
	}

	virtual ~ComparableGrid();

	bool operator<(const ComparableGrid &cgrid) const;

};

struct compareGrids
{

bool operator()(ComparableGrid *a, ComparableGrid *b)
{
	return *a < *b;
}

};


#endif
