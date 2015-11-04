#ifndef GridDependentData_h
#define GridDependentData_h

#include "Grid.h"

// Grid Dependent Data. Data, which is used for the calculation iterative operator (see Operator.h), which depends on the grid.
// In the case of RISM grid dependent are:
//   - potential u_{s\alpha}(r),
//   - susceptibility chi_{s\alpha}
//   - intramolecular correlation functions w_{s\alpha}
// and so on... 

#include "Object.h"
class GridIndependentData;

class GridDependentData : public Object
{
protected:

	Grid *m_grid;
	GridIndependentData *m_gridIndependent;

public:
	GridDependentData(Grid *grid ,
			  GridIndependentData *gridIndependent = NULL)
	{
		m_grid = grid;
		m_grid->retain();
		m_gridIndependent = gridIndependent;
	}

	virtual ~GridDependentData() {NULL_DELETE(m_grid);}
	virtual Grid *getGrid()  
	{
		return m_grid;
	}

	virtual GridIndependentData *getGridIndependent()
	{
		return m_gridIndependent;
	}

};



#endif
