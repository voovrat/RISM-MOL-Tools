#include "solveLinearSystem.h"

#include <stdio.h>
#include <stdlib.h>
#include "Exception.h"

#include "Settings.h"
#include <math.h>

extern "C" {

void dgesv_(	int* n,
		int* nrhs, 
		double* a,
		int* lda,
             	int* ipiv, 
		double* b,
		int* ldb,
                int *info 
		);

}
/*      SUBROUTINE DGESV( N, NRHS, A, LDA, IPIV, B, LDB, INFO )
*
*  -- LAPACK driver routine (version 3.2) --
*  -- LAPACK is a software package provided by Univ. of Tennessee,    --
*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
*     November 2006
*
*     .. Scalar Arguments ..
      INTEGER            INFO, LDA, LDB, N, NRHS
*     ..
*     .. Array Arguments ..
      INTEGER            IPIV( * )
      DOUBLE PRECISION   A( LDA, * ), B( LDB, * )
*     ..
*
*  Purpose
*  =======
*
*  DGESV computes the solution to a real system of linear equations
*     A * X = B,
*  where A is an N-by-N matrix and X and B are N-by-NRHS matrices.
*
*  The LU decomposition with partial pivoting and row interchanges is
*  used to factor A as
*     A = P * L * U,
*  where P is a permutation matrix, L is unit lower triangular, and U is
*  upper triangular.  The factored form of A is then used to solve the
*  system of equations A * X = B.
*
*  Arguments
*  =========
*
*  N       (input) INTEGER
*          The number of linear equations, i.e., the order of the
*          matrix A.  N >= 0.
*
*  NRHS    (input) INTEGER
*          The number of right hand sides, i.e., the number of columns
*          of the matrix B.  NRHS >= 0.
*
*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
*          On entry, the N-by-N coefficient matrix A.
*          On exit, the factors L and U from the factorization
*          A = P*L*U; the unit diagonal elements of L are not stored.
*
*  LDA     (input) INTEGER
*          The leading dimension of the array A.  LDA >= max(1,N).
*
*  IPIV    (output) INTEGER array, dimension (N)
*          The pivot indices that define the permutation matrix P;
*          row i of the matrix was interchanged with row IPIV(i).
*
*  B       (input/output) DOUBLE PRECISION array, dimension (LDB,NRHS)
*          On entry, the N-by-NRHS matrix of right hand side matrix B.
*          On exit, if INFO = 0, the N-by-NRHS solution matrix X.
*
*  LDB     (input) INTEGER
*          The leading dimension of the array B.  LDB >= max(1,N).
*
*  INFO    (output) INTEGER
*          = 0:  successful exit
*          < 0:  if INFO = -i, the i-th argument had an illegal value
*          > 0:  if INFO = i, U(i,i) is exactly zero.  The factorization
*                has been completed, but the factor U is exactly
*                singular, so the solution could not be computed.
*
*  =====================================================================*/

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



Integer solveLinearSystem(Matrix<Real> *A,
			Matrix<Real> *B,
			Matrix<Real> *X
			)
{
	int M = (int)A->getNumRows();
	int N = (int)A->getNumCols();
	int nrhs = (int)B->getNumCols();
	
	if(B->getNumRows()!=M || X->getNumRows()!=N || X->getNumCols()!=nrhs)
		throw new Exception(NULL,"solveLinearSystem: sizeos of A,B,X are not consistent");

	double *LAPACK_A = (double *)malloc( M*N *sizeof(double));	
	double *LAPACK_B = (double *)malloc( M*nrhs*sizeof(double));
	int *P = (int *)malloc(N*sizeof(int));
	

	A->toColumnArray(LAPACK_A);
	B->toColumnArray(LAPACK_B);

	double anorm;
	
	anorm=dlange_(	"1",	//const char* norm,
			&N,	//int *m,
			&N,	//int *n,
			LAPACK_A,//double *a,
			&N,	//int *lda,
			NULL	//double *work 	//size m for inf norm, NULL otherwise
		);


	int result;

	dgesv_(	&N,//	N
		&nrhs,	 // NRHS,
		LAPACK_A,// A,
		&N,	// LDA, 
		P,	//IPIV, 
		LAPACK_B,//B, 
		&N,	//LDB, 
		&result //INFO 
	);

	X->fromColumnArray(LAPACK_B);

/*	double rcond,cond;
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
	printf("COND=%lf;   result=%d\n",cond,result);

	if(cond>MAX_COND) result=1;

	// det(A) = det(PLU)=det(P)*det(L)*det(U)
	// det(P)=+-1, det(L)=1, det(U) = Prod diag(U) -> ergo abs(det) = abs(Prod(diag(U)))
*/
/*	if(M==N)
	{
		Integer i;
		Real D=1;
		Real *ptr = LAPACK_A; // now it contains LU decomposition (see description)
		
		for(i=0;i<M;i++)
		{
			D=D*(*ptr);
			ptr += (M+1); // diagonal elements have numbers 0, M+1, 2M+2,...(M-1)M+M-1=M^2-1
		}
			
		Real Mul=1;
		for(i=0;i<M;i++)
		{
			if(A->getAt(i,i)<MIN_DETERMINANT) continue;
			Mul = Mul*A->getAt(i,i);
		}

		if(fabs(D/Mul)<MIN_DETERMINANT) result = 1;		
	}
*/
	free(LAPACK_A);
	free(LAPACK_B);
	free(P);

	return (result==0);

}
