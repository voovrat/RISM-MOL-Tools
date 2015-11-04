#ifndef GridNumerator_h
#define GridNumerator_h

class GridIndex;
class Grid;

#include "Object.h"
#include "Comparator.h"

class GridNumerator : public Object
{
protected:

	GridIndex *m_gridIndex;
	Grid **m_grids;
	Integer m_Ngrids;


public:

	GridNumerator(	Grid **grids,
			Integer NGrids,
			Comparator<Grid> *gridComparator
		     );

	virtual ~GridNumerator();

	Integer getNgrids()
	{
		return m_Ngrids;
	}

	Integer getIndex(Grid *);
	Grid *getGrid(Integer );

};


class GridNumeratorFactory : public Object 
{
public:
	virtual GridNumerator *createGridNumerator() = 0;

};

#endif
