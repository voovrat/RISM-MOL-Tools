#include <math.h>

#include "rotationMatrix.h"

#include "mulMatrix.h"

void rotationMatrix(	double psi,    // rot x
			double theta,  // rot y
			double phi,    // rot z
			double *result // 3x3 matrix, xstep=1, ystep=3
			)
{

#define COS_PSI 1
#define SIN_PSI 0

#define COS_THETA 1
#define SIN_THETA 0

#define COS_PHI 1
#define SIN_PHI 0

double RotX[9] = { 	1,	0,	 	0,
			0,	COS_PHI, 	SIN_PHI,
			0 	-SIN_PHI,	COS_PHI };

double RotY[9] = {	COS_THETA,	0,	SIN_THETA,
				0,		1,	0,
			-SIN_THETA,	0,	COS_THETA
			};

double RotZ[9] = {	COS_PSI,	SIN_PSI,	0,
			-SIN_PSI,	COS_PSI,	0,
			0,		0,		1};

double tmp[9];

double cos_phi = cos(phi);
double sin_phi = sin(phi);
double cos_theta = cos(theta);
double sin_theta = sin(theta);
double cos_psi = cos(psi);
double sin_psi = sin(psi);

RotX[4] = cos_phi;
RotX[5] = sin_phi;
RotX[7] = -sin_phi;
RotX[8] = cos_phi;

RotY[0] = cos_theta;
RotY[2] = sin_theta;
RotY[6] = -sin_theta;
RotY[8] = cos_theta;

RotZ[0] = cos_psi;
RotZ[1] = sin_psi;
RotZ[3] = -sin_psi;
RotZ[4] = cos_psi;

//tmp = RotX*RotY
mulMatrix( 	RotX,	//double *A, // MxN
		1,	//int A_xstep, 
		3,	//int A_ystep,	
		RotY,	//double *B, //NxK 
		1,	//int B_xstep,
		3,	//int B_ystep,
		3,	//int M, 	
		3,	//int N,
		3,	//int K,
		tmp,	//double *result, // MxK
		1,	//int result_xstep,
		3	//int result_ystep
		);

// result = tmp*RotZ = RotX*RotY*RotZ
mulMatrix( 	tmp,	//double *A, // MxN
		1,	//int A_xstep, 
		3,	//int A_ystep,	
		RotZ,	//double *B, //NxK 
		1,	//int B_xstep,
		3,	//int B_ystep,
		3,	//int M, 	
		3,	//int N,
		3,	//int K,
		result,	//double *result, // MxK
		1,	//int result_xstep,
		3	//int result_ystep
		);
}
/*
#include <stdio.h>

main()
{
double R[9];
int i;

rotationMatrix(	0.1,	//double psi,
		0.2,	//double theta,
		0.3,	//double phi,
		R	//double *result // 3x3 matrix, xstep=1, ystep=3
	);
for(i=0;i<9;i++)
printf("%lf\n",R[i]);

return 0;			

}
*/
