#ifndef generateGrid3DRISM_h
#define generateGrid3DRISM_h

#include "Settings.h"
class Grid3DRISM; 
class MoleculeCoordinates;

// creates grid with dx=dy=dz=dr and given buffer for a given molecule

void generateGrid3DRISM(MoleculeCoordinates *moleculeCoordinates,
			Real buffer,
			Real dr,	
			Grid3DRISM *result, //out
			Integer align = 8
			);


#endif
