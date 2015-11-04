#include "Matrix.h"

template<class T>
void Matrix<T>::toRowArray(T *array)
{
	Integer M = getNumRows();
	Integer N = getNumCols();
	T *ptr = array;

	Integer i,j;
	for(i=0;i<M;i++)
		for(j=0;j<N;j++, ptr++)
			*ptr = getAt(i,j);
}

template<class T>
void  Matrix<T>::fromRowArray(T *array)
{
	Integer M = getNumRows();
	Integer N = getNumCols();
	T *ptr = array;

	Integer i,j;
	for(i=0;i<M;i++)
		for(j=0;j<N;j++, ptr++)
			setAt(i,j,*ptr);
}

template<class T>
void Matrix<T>::toColumnArray(T *array)
{
	Integer M = getNumRows();
	Integer N = getNumCols();
	T *ptr = array;

	Integer i,j;
	for(j=0;j<N;j++)
		for(i=0;i<M;i++, ptr++)
			*ptr = getAt(i,j);
}

template<class T>
void Matrix<T>::fromColumnArray(T *array)
{
	Integer M = getNumRows();
	Integer N = getNumCols();
	T *ptr = array;

	Integer i,j;
	for(j=0;j<N;j++)
		for(i=0;i<M;i++, ptr++)
			setAt(i,j,*ptr);
}

template<class T>
void Matrix<T>::mul(Matrix<T> *B,Matrix<T> *Result) // Result = this * B
{
    int m = this->getNumRows();
    int n = this->getNumCols();
    int k = B->getNumCols();    

    if( n != B->getNumRows() || Result->getNumRows()!=m || Result->getNumCols()!=k ) 
    {
        throw new Exception(this,"Matrix.mul: incorrect number of rows/columns in matrices!");
    }

    int i,j,s;
    for(i=0;i<m;i++)
    for(j=0;j<k;j++)
    { T S = 0;
        for(s=0;s<n;s++)
        {
            S += this->getAt(i,s) * B->getAt(s,j);
        }
        Result->setAt(i,j,S);
    }
}


#define Matrix_binop(opname, opcode )  \
template<class T>                   \
void Matrix<T>::opname(Matrix<T> *B,Matrix<T> *Result) \
{                                                   \
  int m = this->getNumRows();                       \
  int n = this->getNumCols();                       \
  if( m != B->getNumRows() || n != B->getNumCols() || Result->getNumRows()!=m || Result->getNumCols()!=n ) \
        throw new Exception(this,"Matrix." #opname ": incorrect number of rows/columns in matrices!");      \
  int i,j;                  \
  for(i=0;i<m;i++)          \
  for(j=0;j<k;j++)          \
       Result->setAt(i,j, opcode ); \
}

Matrix_binop(add, this->getAt(i,j) + B->getAt(i,j) )
Matrix_binop(sub, this->getAt(i,j) - B->getAt(i,j) )

#define Matrix_monop(opname, opcode )  \
template<class T>                   \
void Matrix<T>::opname(Matrix<T> *A) \
{                                                   \
  int m = this->getNumRows();                       \
  int n = this->getNumCols();                       \
  if( m != A->getNumRows() || n != A->getNumCols() )  \
        throw new Exception(this,"Matrix." #opname ": incorrect number of rows/columns in matrices!");      \
  int i,j;                  \
  for(i=0;i<m;i++)          \
  for(j=0;j<k;j++)          \
        opcode;             \
}


Matrix_monop(copyFrom, this->setAt(i,j, A->getAt(i,j) ) )
Matrix_monop(copyTo, A-setAt(i,j, this->getAt(i,j) ) )


template<class T>                   
void Matrix<T>::mulScalar(T scale, Matrix<T> *Result) 
{                                                   
  int m = this->getNumRows();                       
  int n = this->getNumCols();                       
  if( m != Result->getNumRows() || n != Result->getNumCols() )  
        throw new Exception(this,"Matrix.mulScalar : incorrect number of rows/columns in matrices!");      
  int i,j;                  
  for(i=0;i<m;i++)          
  for(j=0;j<k;j++)          
        Result->setAt(i,j, scale * this->getAt(i,j) );
}


        virtual void copyFrom(Matrix<T> *src);
        virtual void copyTo(Matrix<T> *dst); 

        virtual void mul(Matrix<T> *B,Matrix<T> *Result); // Result = this * B
        virtual void mulScalar(T scalar, Matrix<T> *Result);

        virtual void add(Matrix<T> *B,Matrix<T> *Result); // Result = this + B
        virtual void add(Matrix<T> *B) {add(B,this);} // this +=B

        virtual void sub(Matrix<T> *B,Matrix<T> *Result); // Result = this + B
        virtual void sub(Matrix<T> *B) {sub(B,this);} // this -=B


 
