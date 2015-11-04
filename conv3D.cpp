#include "Settings.h"
#include "Grid3DRISM.h"
#include "FFTW3D.h"
#include "ArrayOperations.h"

#include <complex>
#include <stdlib.h>


void conv3D(	Real *A,
		Real *B,
		Grid3DRISM *grid,
		Real *C // out: C=conv(A,B)
		)
{
FFTW3D *fftw = FFTW3D::getInstance();
Integer Nk = grid->getNx() * grid->getNy() * ( grid->getNz()/2 + 1 );
Integer Nr = grid->getNx() * grid->getNy() * grid->getNz();

std::complex<Real> *FA = (std::complex<Real> *)malloc( Nk * sizeof(std::complex<Real> ));

std::complex<Real> *FB = (std::complex<Real> *)malloc( Nk * sizeof(std::complex<Real> ));


Real k1,k2,k3;

k1 =  fftw->fft(A,	//Real *in,
		FA,	//std::complex<Real> *out,
		grid	//Grid3DRISM *grid
	);

k2 =  fftw->fft(B,	//Real *in,
		FB,	//std::complex<Real> *out,
		grid	//Grid3DRISM *grid
	);

//FA = FA*FB
mulArray<std::complex<Real> >(	FA,	//DataType *dst,
				FB,	//DataType *src,
				Nk	//Integer N 
				);	
free(FB);


k3 = fftw->ifft(FA,	//std::complex<Real> *in,
		C,	//Real *out,
		grid	//Grid3DRISM *grid
		);

free(FA);

mulArrayScalar<Real,Real>(	C,	//DataType *dst,
				k1*k2*k3,	//ScalarType scalar,
				Nr	//Integer N
			);
}
/*
#include "writeDoubleArrayToFile.h"
#include "saveGrid3DRISM.h"


main()
{
Real R=5;

Grid3DRISM grid(4*R,4*R,4*R,1,1,1);

saveGrid3DRISM(	&grid,	//Grid3DRISM *grid,
		"",	//const char *fileNamePrefix,
		".grd"	//const char *fileNameSuffix
		);


Integer N = grid.getNx() * grid.getNy() * grid.getNz();

Real *A = (Real *)malloc( N * sizeof(Real) );
Real *B = (Real *)malloc( N * sizeof(Real) );
Real *C = (Real *)malloc( N * sizeof(Real) );

Real *pA=A,*pB=B;
Real VA,VB;

GAMMA_FOR(&grid)
{
//	V = ( GAMMA_FOR_R < R);
	VB = ( 	fabs(GAMMA_FOR_X) < R/2 && 
		fabs(GAMMA_FOR_Y) < R/2 && 
		fabs(GAMMA_FOR_Z) < R/2 );

	VA =( 	fabs( fabs(GAMMA_FOR_X) - R)<0.5  || 
		fabs( fabs(GAMMA_FOR_Y) - R)<0.5  ||
		fabs( fabs(GAMMA_FOR_Z) - R)<0.5 );

	*pA = VA; *pB = VB;

	pA++; pB++;
}
END_GAMMA_FOR


writeDoubleArrayToFile(	"A.3d",	//const char *fname,
			A,	//Real *x,
			N	//Integer N
			);

writeDoubleArrayToFile(	"B.3d",	//const char *fname,
			B,	//Real *x,
			N	//Integer N
			);

conv3D(	A,	//Real *A,
	B,	//Real *B,
	&grid,	//Grid3DRISM *grid,
	C	//Real *C // out: C=conv(A,B)
	);

writeDoubleArrayToFile(	"C.3d",	//const char *fname,
			C,	//Real *x,
			N	//Integer N
			);

free(A);
free(B);
free(C);

return 0;
}
*/
