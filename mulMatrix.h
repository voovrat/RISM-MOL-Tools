#ifndef mulMatrix_h
#define mulMatrix_h

// Multiply matrices
// Matrices are given as 1D arrays
// in the MxN matrix A
// the data in each row is located with step xstep
// the data in each column is located with step ystep
//
// Typically, xstep=1, ystep=N.
// However, for transposed matrix xstep=M, ystep=1 (so one can simply transpose the matrix without any moving of the data)


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
		);

#endif

