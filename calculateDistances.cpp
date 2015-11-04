#include "calculateDistances.h"

#include <math.h>
#include "Settings.h"

void calculateDistances(Real *coors,
			Integer Nsites,
			Real *distances,
			Integer Dim //=3
			)
{
Integer i,j,k;

for(i=0;i<Nsites;i++)
{
	Real *pcoors1 = coors + i*Dim;
	for(j=i;j<Nsites;j++)
	{
		Real *pcoors2 = coors + j*Dim;
		Real S=0;
		for(k=0;k<Dim;k++)
		{
			Real dx = pcoors1[k] - pcoors2[k];
			S += dx*dx;
		}

		Real d = sqrt(S);
		distances[ i*Nsites + j ] = d;
		distances[ j*Nsites + i ] = d;
	}

}

}

/*
#include <stdio.h>

main()
{
#define Nsites 4

Real coors[Nsites*2] = { 	0,	0,
			1,	0,
			0,	1,
			1,	1  };

Real distances[Nsites*Nsites];

calculateDistances(	coors,	//Real *coors,
			Nsites,	//Integer Nsites,
			distances,	//Real *distances,
			2	//Integer Dim //=3
			);
int i,j;
for(i=0;i<Nsites;i++)
{
	for(j=0;j<Nsites;j++)
	{
		printf("%lg\t",distances[i*Nsites+j]);
	
	}
	printf("\n");
}

return 0;
}
*/
