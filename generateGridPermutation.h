#ifndef generateGridPermutation_h
#define generateGridPermutation_h

#include "Settings.h"


// generates P such, that grid[P[i]], i=0..N is ascending 
inline void generateGridPermutation(	Integer N,
					Integer *P)
{
Integer i;
Integer N2 = N/2;
for(i=0;i<=N2;i++) P[i+N2-1]=i;
for(i=N2+1;i<N;i++) P[i-N2-1]=i;

}

#endif
