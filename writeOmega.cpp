#include "Settings.h"
#include <stdio.h>
#include <stdlib.h>

inline void printOmegaLine(FILE *f,Integer rdfNum,Integer multiplicity, Real dist)
{

fprintf(f,"%ld\t%lg\t%lg\n",rdfNum,1.0/multiplicity,dist);

}

void writeOmega(Integer *RDFNum,
		Integer *Joins,
		Real *distances,
		Integer BigN,
		FILE *f)
{
int i,j,k;
Integer *pNum,*pJoins;


Real *distList = (Real *)malloc(BigN * sizeof(Real));

for(i=0;i<BigN;i++)
{
	int offset = i*BigN + i;
		
	pNum = RDFNum + offset;
	pJoins = Joins + offset;
	for(j=i;j<BigN;j++,pNum++,pJoins++)
	{
		if( *pNum == -1 ) continue;
		
		if( *pJoins == 0 )
		{
			Real d = distances[i*BigN + j]; 
			if( d >=0 )
			{
				printOmegaLine(f,*pNum,1,d);
			}
			continue;
		}

		Integer NOmega = 0;
		for(k=0;k<BigN;k++)
		{
			if(Joins[j + BigN*k]==1)
			{
				distList[NOmega] = distances[j + BigN*k];
				NOmega++;
			}//if Joins
		}//for k		

		for(k=0;k<NOmega;k++)
		{
			printOmegaLine(f,*pNum,NOmega,distList[k]);
		}//for k


	}//for j

}//for i


}
