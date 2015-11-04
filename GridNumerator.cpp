#include "GridNumerator.h"

#include "GridIndex.h"
#include "Grid.h"
#include "GridDataFactory.h"

#include <stdlib.h>

class Counter : public Object
{
protected:
	Integer m_N;

public:
	Counter(Integer N)
	{
		m_N = N;
	}		

	Integer getN()
	{
		return m_N;
	}
};

class GridCounterFactory : public  GridDataFactory
{
protected:
	Integer m_counter;

public:
	GridCounterFactory()
	{
		m_counter = 0;
	}

	virtual Object *createData(Grid *grid)
	{
		Object *obj = new Counter(m_counter);
		m_counter++;
		return obj;
	}
};


GridNumerator::GridNumerator(	Grid **grids,
				Integer Ngrids,
				Comparator<Grid> *gridComparator
		     	)
{
	GridCounterFactory *gridCounterFactory = new GridCounterFactory();

	addToDeleteList(gridCounterFactory);

	m_gridIndex = new GridIndex(
					gridCounterFactory,	//GridDataFactory *gridDataFactory,
					gridComparator		//Comparator<Grid> *gridComparator
				);

	m_grids = (Grid **)malloc( Ngrids * sizeof(Grid *) );

	m_Ngrids = Ngrids;

	Integer i;
	for(i=0; i<Ngrids; i++)
	{
		Counter *counter = (Counter *)m_gridIndex->findData(grids[i]);
		m_grids[counter->getN()] = grids[i];
	}

	

}

GridNumerator::~GridNumerator()
{
	free(m_grids);
	NULL_DELETE(m_gridIndex);
}

Integer GridNumerator::getIndex(Grid *grid)
{
	Counter *counter = (Counter *)m_gridIndex->findData(grid);
	return counter->getN();
}

Grid * GridNumerator::getGrid(Integer index)
{
	return m_grids[index];
}


