#include "RotatedCoorsTable.h"
#include <stdlib.h>
#include <math.h>

#include "mulMatrix.h"
#include "rotationMatrix.h"

	
void RotatedCoorsTable::init(Real *coors,Integer Nsites,Integer Nrotations)
{
uninit();


m_angles = (Real *)malloc(Nrotations * sizeof(Real));
Real dAng = 2*M_PI/Nrotations;

Integer i;
for(i=0;i<Nrotations;i++)
	m_angles[i] = dAng * i;



m_Nrotations = Nrotations;
Integer N3 = Nrotations * Nrotations * Nrotations;

m_coorsTable = (Real **)malloc( N3 * sizeof(Real *));

RotatedCoorsIterator it(this);

Real Rot[9];	

while(!it.isOver())
{

	Real *rotatedCoors = (Real *)malloc( Nsites * 3 * sizeof(Real));
	it.setData(rotatedCoors);

	
//	printf("%ld %ld %ld %lf %lf %lf %lf\n",it.m_phiId,it.m_thetaId,it.m_psiId,it.getPhi(),it.m_angles[it.m_thetaId],it.getTheta(),it.getPsi());
	
	rotationMatrix(	it.getPsi(),	//double psi,
			it.getTheta(),	//double theta,
			it.getPhi(),	//double phi,
			Rot	//double *result // 3x3 matrix, xstep=1, ystep=3
			);


	mulMatrix(	Rot,	//double *A, // MxN
			1,	//int A_xstep, 
			3,	//int A_ystep,	
			coors,	//double *B, //NxK 
			3,	//int B_xstep,  // because B=transpose(coors), size(B) = 3 x nlin
			1,	//int B_ystep,
			3,	//int M, 	
			3,	//int N,
			Nsites,	//int K,
			rotatedCoors,	//double *result, // MxK
			3,	//int result_xstep, //size out = 3 x nlin, it should be transposed
			1	//int result_ystep
		);

	

	it.next();

}//while !it.isOver


}


void RotatedCoorsTable::uninit()
{

if(m_coorsTable)
{
	RotatedCoorsIterator it(this);

	while(!it.isOver())
	{
		free(it.getData());
		it.next();
	}//while

	free(m_coorsTable);
}

if(m_angles)
	free(m_angles);

m_coorsTable=NULL;
m_angles=NULL;
m_Nrotations=0;

}

/*
#include "readDoubleTableSimple.h"
#include "stdio.h"

main()
{

Real *coors;
Integer nlin,ncol;

readDoubleTableSimple(	"water.XYZ",	//const char *fname,
			&nlin,	//Integer *nlin,	//out
			&ncol,	//Integer *ncol,	//out
			&coors	//Real **result //out, will be allocated
			);

RotatedCoorsTable rotatedCoors;

rotatedCoors.init(	coors,	//Real *coors,
			3,	//Integer Nsites,
			4	//Integer Nrotations
		);


RotatedCoorsIterator it(&rotatedCoors);

while(!it.isOver())
{
	//writeDoubleTableToFile("/dev/stdout",it.getData(),9);
	Real *rotatedCoors = it.getData();
	
	int i;
	for(i=0;i<3;i++)
		printf("%lf\t%lf\t%lf\n",
				rotatedCoors[i*3],
				rotatedCoors[i*3+1],
				rotatedCoors[i*3+2]
			);
					
	
	it.next();
}




free(coors);

}
*/
