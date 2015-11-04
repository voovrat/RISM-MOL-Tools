#ifndef ExtendGrid_h
#define ExtendGrid_h

#include "GridNumerator.h"
#include "BinaryOperation.h"

class ExtendGrid : public BinaryOperation<Grid *>
{
protected:
	GridNumerator *m_gridNumerator;

public:
	ExtendGrid(GridNumerator *gridNumerator) 
	{
		m_gridNumerator = gridNumerator;
	}

	virtual void operator()(Grid *src,Grid *dst)
	{
		Integer id = m_gridNumerator->getIndex(src);
		Grid *result = m_gridNumerator->getGrid(id+1);

		result->copy(dst);
	}

};


#endif
