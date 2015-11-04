#ifndef GridIndex_h
#define GridIndex_h

#include "Object.h"
#include <map>


class Grid;
class GridDataFactory;

#include "ComparableGrid.h"
#include "Comparator.h"


class GridIndex : public Object
{
protected: 
	typedef std::map<ComparableGrid*,Object *,compareGrids> DATA_MAP;
	typedef std::map<ComparableGrid*,Object *,compareGrids>::iterator    DATA_MAP_ITERATOR;

	DATA_MAP m_dataMap;

	GridDataFactory *m_gridDataFactory;
	Comparator<Grid> *m_gridComparator;

public:
	GridIndex(GridDataFactory *gridDataFactory,
			Comparator<Grid> *gridComparator)
	{
		m_gridDataFactory = gridDataFactory;
		m_gridComparator = gridComparator;
	}

	virtual ~GridIndex();

	Object *findData(Grid *grid);
	

};

#endif
