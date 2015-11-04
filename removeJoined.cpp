#include "Settings.h"
#include "ArrayOperations.h"

// Joins is the matrix where at (i,j) stays 1 if atoms i and j are identical and 0 elsewhere
//  removeJoined left only one (first) of 1s in each line. 
// if (i,j)=1 and i!=j, i<j, than the row and col j are set to -1
//

void removeJoined(	Integer *Joins,
			Integer N,
			Integer *RemovedJoins)
{

copyArray<Integer>(RemovedJoins,Joins,N*N);

int i,j,k;

for(i=0;i<N;i++)
{
	Integer *pJoins = Joins + i*N + i+1;
	for(j=i+1;j<N;j++,pJoins++)
	{
		if(*pJoins==1)
		{
			for(k=0;k<N;k++)
			{
				RemovedJoins[j*N+k]=-1;
				RemovedJoins[k*N+j]=-1;
			}//for k	
		}//if pJoins
	}//for i
}//for j

}



