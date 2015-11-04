#include "Settings.h"

void numerateRDFs(	Integer *removedJoins, //in-out
			Integer BigN
		 )
{

int i,j;
Integer *pR = removedJoins;
Integer nrdf=0;
for(i=0;i<BigN;i++)
{
	pR = removedJoins + i*BigN + i;
	for(j=i;j<BigN;j++,pR++)
	{
		if(*pR!=-1) 
		{	
			*pR = nrdf;
			nrdf++;
		}
	}//for j
}//for i

}
