#include "mulMatrix.h"
// why so strange?
// we will multiply rotation matrix A (3x3) by coordinated XYZ (Kx3)
// and we will want to have result also coordinated XYZ1 (Kx3)
// so, typically we will need to do the following:
// 1) XYZ -> XYZ' (3xK)
// 2) XYZ1 = A * XYZ' ( 3xK)
// 3) XYZ1 -> XYZ1' (Kx3)
// however, to avoid transpositions, we can make everything simplier: just give A in row-col format and XYZ/XYZ1 in col-row format. 

void mulMatrix( double *A, // MxN
		int A_xstep,
		int A_ystep,	
		double *B, //NxK 
		int B_xstep,
		int B_ystep,
		int M, 	
		int N,
		int K,
		double *result, // MxK
		int result_xstep,
		int result_ystep
		)
{
int i,j,k;
double *pA,*pB,*pR;

pA=A; pB=B; pR=result;
for(i=0; i<M; i++)
{
	pA = A + A_ystep*i;
	pR = result+i*result_ystep;

	for(j=0; j<K; j++)
	{

		pB = B+j*B_xstep;
		
		double S=0;
		for(k=0;k<N;k++)
		{
			S+=*pA * *pB;
			pA+=A_xstep; pB+=B_ystep;
		}
		*pR = S;

		pA -= A_xstep*N;
		pR+=result_xstep;
	 
	}
}	


}
/*
#include <stdio.h>

main()
{
double A[8]={1,2,3,4,5,6,7,8}; // 4x2  [ 1 2; 3 4; 5 6; 7 8]
double B[6]={1,2,3,4,5,6}; // 2x3 [1 3 5; 2 4 6];
double C[12];
int i;

//mulMatrix(A,B,4,2,3,C);

mulMatrix(
	A,	//double *A, // MxN
	1,	//int A_xstep,
	2,	//int A_ystep,	
	B,	//double *B, //NxK 
	2,	//int B_xstep,
	1,	//int B_ystep,
	4,	//int M, 	
	2,	//int N,
	3,	//int K,
	C,	//double *result // MxK
	4,	//int result_xstep,
	1	//int result_ystep
	);


for(i=0;i<12;i++)
{
printf("%lf\n",C[i]);
}
return 0;
}
*/
