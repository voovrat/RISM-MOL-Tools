#include "Settings.h"

void getMultiplicities(	Integer *Joins,
			Integer N,
			Integer *multiplicities)
{

int i,j;
Integer *pJoins = Joins;
Integer *pMult = multiplicities;

for(i=0;i<N;i++,pMult++)
{
	*pMult=0;
	for(j=0;j<N; j++, pJoins++ )
	{
		*pMult+=*pJoins;
	}
}

}
