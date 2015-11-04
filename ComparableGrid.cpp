#include "ComparableGrid.h"

#include "CompareGrids.h"
#include "Grid.h"
#include "Comparator.h"

ComparableGrid::ComparableGrid(	Grid *grid,
		    		Comparator<Grid> *comparator)
{
	m_grid = grid;
	m_comparator = comparator;
}

ComparableGrid::~ComparableGrid()
{

}

bool ComparableGrid::operator<(const ComparableGrid &cgrid) const
{
	return m_comparator->isLess(m_grid,cgrid.m_grid);
}
