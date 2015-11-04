#include "ExtendGridNumeratorFactory.h"

#include <stdlib.h>
#include "Grid3DRISM.h"
#include "generateGrid3DRISM.h"

#include "GridComparator3DRISM.h"

#include "Pointer.h"

ExtendGridNumeratorFactory::ExtendGridNumeratorFactory(	
					MoleculeCoordinates *moleculeCoordinates,
					Real maxBuffer,
					Real spacing,
					Integer Ngrids,
					Real bufferDecayFactor)
{
	Real buffer=maxBuffer;

	Integer i;
	for(i=0; i<Ngrids-1; i++)
	{
		buffer /= bufferDecayFactor;
	}
	

	Grid3DRISM **grids = ( Grid3DRISM **)malloc( Ngrids * sizeof(Grid3DRISM *) );
	for(i=0; i<Ngrids; i++)
	{
		grids[i] = new Grid3DRISM();

		generateGrid3DRISM(	moleculeCoordinates,	//MoleculeCoordinates *coors,
					buffer,		//Real buffer,
					spacing,	//Real dr,	
					grids[i],	//Grid3DRISM *result, //out
					(1<<(Ngrids))//Integer ALIGN 
			);

		buffer *= bufferDecayFactor;

	}

	m_gridNumerator = new GridNumerator(
			(Grid **)grids,				//Grid **grids,
			Ngrids,					//Integer NGrids,
			GridComparator3DRISM::getInstance()	//Comparator<Grid> *gridComparator
		     );

	for(i=0; i<Ngrids;i++)
	{
		m_gridNumerator->addToDeleteList(new Pointer(grids[i]));
	}
	
	m_gridNumerator->addToDeleteList(new Pointer(grids));

}
