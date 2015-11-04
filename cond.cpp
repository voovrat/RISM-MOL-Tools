#include "cond.h"
#include "Matrix.h"
#include "Exception.h"

#include <stdlib.h>

extern "C" {

void dgecon_(	const char* norm,
		int *n,
		double *a,
		int *lda,
		double *anorm,	//out
		double *rcond,	//out
		double *work, 	//4*n
		int	*iwork,	//n
		int 	*info	//out
		);

}

 /*    SUBROUTINE DGECON( NORM, N, A, LDA, ANORM, RCOND, WORK, IWORK,
     $                   INFO )
*
*  -- LAPACK routine (version 3.2) --
*  -- LAPACK is a software package provided by Univ. of Tennessee,    --
*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
*     November 2006
*
*     Modified to call DLACN2 in place of DLACON, 5 Feb 03, SJH.
*
*     .. Scalar Arguments ..
      CHARACTER          NORM
      INTEGER            INFO, LDA, N
      DOUBLE PRECISION   ANORM, RCOND
*     ..
*     .. Array Arguments ..
      INTEGER            IWORK( * )
      DOUBLE PRECISION   A( LDA, * ), WORK( * )
*     ..
*
*  Purpose
*  =======
*
*  DGECON estimates the reciprocal of the condition number of a general
*  real matrix A, in either the 1-norm or the infinity-norm, using
*  the LU factorization computed by DGETRF.
*
*  An estimate is obtained for norm(inv(A)), and the reciprocal of the
*  condition number is computed as
*     RCOND = 1 / ( norm(A) * norm(inv(A)) ).
*
*  Arguments
*  =========
*
*  NORM    (input) CHARACTER*1
*          Specifies whether the 1-norm condition number or the
*          infinity-norm condition number is required:
*          = '1' or 'O':  1-norm;
*          = 'I':         Infinity-norm.
*
*  N       (input) INTEGER
*          The order of the matrix A.  N >= 0.
*
*  A       (input) DOUBLE PRECISION array, dimension (LDA,N)
*          The factors L and U from the factorization A = P*L*U
*          as computed by DGETRF.
*
*  LDA     (input) INTEGER
*          The leading dimension of the array A.  LDA >= max(1,N).
*
*  ANORM   (input) DOUBLE PRECISION
*          If NORM = '1' or 'O', the 1-norm of the original matrix A.
*          If NORM = 'I', the infinity-norm of the original matrix A.
*
*  RCOND   (output) DOUBLE PRECISION
*          The reciprocal of the condition number of the matrix A,
*          computed as RCOND = 1/(norm(A) * norm(inv(A))).
*          computed as RCOND = 1/(norm(A) * norm(inv(A))).
*
*  WORK    (workspace) DOUBLE PRECISION array, dimension (4*N)
*
*  IWORK   (workspace) INTEGER array, dimension (N)
*
*  INFO    (output) INTEGER
*          = 0:  successful exit
*          < 0:  if INFO = -i, the i-th argument had an illegal value
*/


extern "C" {

double dlange_(	const char* norm,
		int *m,
		int *n,
		double *a,
		int *lda,
		double *work 	//size m for inf norm, NULL otherwise
		);

}
/*
     DOUBLE PRECISION FUNCTION DLANGE( NORM, M, N, A, LDA, WORK )
*
*  -- LAPACK auxiliary routine (version 3.2) --
*  -- LAPACK is a software package provided by Univ. of Tennessee,    --
*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
*     November 2006
*
*     .. Scalar Arguments ..
      CHARACTER          NORM
      INTEGER            LDA, M, N
*     ..
*     .. Array Arguments ..
      DOUBLE PRECISION   A( LDA, * ), WORK( * )
*     ..
*
*  Purpose
*  =======
*
*  DLANGE  returns the value of the one norm,  or the Frobenius norm, or
*  the  infinity norm,  or the  element of  largest absolute value  of a
*  real matrix A.
*
*  Description
*  ===========
*
*  DLANGE returns the value
*
*     DLANGE = ( max(abs(A(i,j))), NORM = 'M' or 'm'
*              (
*              ( norm1(A),         NORM = '1', 'O' or 'o'
*              (
*              ( normI(A),         NORM = 'I' or 'i'
*              (
*              ( normF(A),         NORM = 'F', 'f', 'E' or 'e'
*
*  where  norm1  denotes the  one norm of a matrix (maximum column sum),
*  normI  denotes the  infinity norm  of a matrix  (maximum row sum) and
*  normF  denotes the  Frobenius norm of a matrix (square root of sum of
*  squares).  Note that  max(abs(A(i,j)))  is not a consistent matrix norm.
*
*  Arguments
*  =========
*
*  NORM    (input) CHARACTER*1
*          Specifies the value to be returned in DLANGE as described
*          above.
*
*  M       (input) INTEGER
*          The number of rows of the matrix A.  M >= 0.  When M = 0,
*          DLANGE is set to zero.
*
*  N       (input) INTEGER
*          The number of columns of the matrix A.  N >= 0.  When N = 0,
*          DLANGE is set to zero.
*
*  A       (input) DOUBLE PRECISION array, dimension (LDA,N)
*          The m by n matrix A.
*
*  LDA     (input) INTEGER
*          The leading dimension of the array A.  LDA >= max(M,1).
*
*  WORK    (workspace) DOUBLE PRECISION array, dimension (MAX(1,LWORK)),
*          where LWORK >= M when NORM = 'I'; otherwise, WORK is not
*          referenced.
*
*/

extern "C" {

	void dgetrf_(	int *m,
			int *n,
			double *a,
			int *lda,
			int *ipiv,
			int *info
		);

}


/*
     SUBROUTINE DGETRF( M, N, A, LDA, IPIV, INFO )
*
*  -- LAPACK routine (version 3.2) --
*  -- LAPACK is a software package provided by Univ. of Tennessee,    --
*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
*     November 2006
*
*     .. Scalar Arguments ..
      INTEGER            INFO, LDA, M, N
*     ..
*     .. Array Arguments ..
      INTEGER            IPIV( * )
      DOUBLE PRECISION   A( LDA, * )
*     ..
*
*  Purpose
*  =======
*
*  DGETRF computes an LU factorization of a general M-by-N matrix A
*  using partial pivoting with row interchanges.
*
*  The factorization has the form
*     A = P * L * U
*  where P is a permutation matrix, L is lower triangular with unit
*  diagonal elements (lower trapezoidal if m > n), and U is upper
*  triangular (upper trapezoidal if m < n).
*
*  This is the right-looking Level 3 BLAS version of the algorithm.
*
*  Arguments
*  =========
*
*  M       (input) INTEGER
*          The number of rows of the matrix A.  M >= 0.
*
*  N       (input) INTEGER
*          The number of columns of the matrix A.  N >= 0.
*
*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
*          On entry, the M-by-N matrix to be factored.
*          On exit, the factors L and U from the factorization
*          A = P*L*U; the unit diagonal elements of L are not stored.
*
*  LDA     (input) INTEGER
*          The leading dimension of the array A.  LDA >= max(1,M).
*
*  IPIV    (output) INTEGER array, dimension (min(M,N))
*          The pivot indices; for 1 <= i <= min(M,N), row i of the
*          matrix was interchanged with row IPIV(i).
*
*  INFO    (output) INTEGER
*          = 0:  successful exit
*          < 0:  if INFO = -i, the i-th argument had an illegal value
*          > 0:  if INFO = i, U(i,i) is exactly zero. The factorization
*                has been completed, but the factor U is exactly
*                singular, and division by zero will occur if it is used
*                to solve a system of equations.
*
*/

// calculate cond of matrix using LAPACK
double	cond(Matrix<Real> *A)
{
	int N = A->getNumRows();
	int result;

	if(A->getNumCols() != N)
		throw new Exception(NULL,"cond : matrix should be square");

	double *LAPACK_A = (double *)malloc( N*N * sizeof(double));
	int *IPIV = (int *)malloc( N * sizeof(int));

	A->toColumnArray(LAPACK_A);

	double anorm;
	
	anorm=dlange_(	"1",	//const char* norm,
			&N,	//int *m,
			&N,	//int *n,
			LAPACK_A,//double *a,
			&N,	//int *lda,
			NULL	//double *work 	//size m for inf norm, NULL otherwise
		);


	
	//dgetrf_(&n, &n, x, &lda, iw, &info);
	 dgetrf_(	&N,	//int *m,
			&N,	//int *n,
			LAPACK_A,//double *a,
			&N,	//int *lda,
			IPIV,	//int *ipiv,
			&result//int *info
		);

	free(IPIV);

	double rcond,cond;
	double *work = (double *) malloc(4*N * sizeof(double));
	int *iwork = (int *)malloc(N * sizeof(int));



	dgecon_("1",	//char* norm,
		&N,	//int *n,
		LAPACK_A,//double *a,
		&N,	//int *lda,
		&anorm,	//double *anorm,	//out
		&rcond,	//double *rcond,	//out
		work,	//double *work, 	//4*n
		iwork,	//int	*iwork,	//n
		&result	//int 	*info	//out
		);

	cond = 1/rcond;
//	printf("COND=%lf;   result=%d\n",cond,result);

	free(LAPACK_A);
	return cond;
}

