#ifndef ExtendGridNumeratorFactory_h
#define ExtendGridNumeratorFactory_h

#include "Settings.h"

#include "GridNumerator.h"

class Grid3DRISM;
class MoleculeCoordinates;

class ExtendGridNumeratorFactory : public GridNumeratorFactory
{
protected:

	GridNumerator *m_gridNumerator;

public:
	
	

	ExtendGridNumeratorFactory(	MoleculeCoordinates *moleculeCoordinates,
					Real maxBuffer,
					Real spacing,
					Integer Ngrids,
					Real bufferDecayFactor
				  );

	virtual GridNumerator *createGridNumerator()
	{
		m_gridNumerator->retain();
		return m_gridNumerator;
	}

	
	
};


#endif
