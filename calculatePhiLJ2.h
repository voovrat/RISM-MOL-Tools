#ifndef calculatePhiLJ2_h
#define calculatePhiLJ2_h

#include "Settings.h"

class Grid1DRISM;
class TabFunction;



// PhiLJ[i][j] = beta * d3ifft( d3fft(U_LJ_long) * chi[i][j] )
// U_LJ_long = -1/r^6 if r<R_cut -1/R_cut^6 else

void calculatePhiLJ2(	Grid1DRISM *grid,
			Real KBT,
			TabFunction ***analyticChiIndex,
			Real **chiMultipliers,
			Real ljPotentialCutoff,	
			Integer numSolventSites,
			TabFunction **phi,	//out
			TabFunction ***phiIndex //out
			);

#endif
