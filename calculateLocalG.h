#ifndef calculateLocalG_h
#define calculateLocalG_h

#include "Settings.h"
class Grid3DRISM;

// calculates product of g's in near x0,y0,z0
Real calculateLocalG( 	Real **g_index, // array of g functions in real (see N )	
			Grid3DRISM * grid, 	
			Real *coors,	// coordinates of the solvent molecule 
			int Nsites, // number of atoms in solvent (NO Multiple nsites!! all multiplicities=1, (eg for water N=3))
			Real x0,
			Real y0,
			Real z0
			);

#endif
