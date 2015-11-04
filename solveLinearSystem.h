#ifndef solveLinearSystem_h
#define solveLinearSystem_h

#include "Matrix.h"

// solves A*X=B.
// return 0, if detA==0, otherwise return 1
Integer solveLinearSystem(	Matrix<Real> *A,
			Matrix<Real> *B,
			Matrix<Real> *X
			);



#endif
