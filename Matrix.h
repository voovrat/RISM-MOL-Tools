#ifndef Matrix_h
#define Matrix_h

#include "Object.h"

template<class T>
class Matrix : public Object
{
public:

	virtual Integer getNumRows() = 0;
	virtual Integer getNumCols() = 0;

	virtual T getAt(Integer row,Integer col)=0;
	virtual void setAt(Integer row,Integer col,T x)=0;

	virtual void toRowArray(T *array);
	virtual void fromRowArray(T *array);

	virtual void toColumnArray(T *array);
	virtual void fromColumnArray(T *array);

        virtual void copyFrom(Matrix<T> *src);
        virtual void copyTo(Matrix<T> *dst); 

        virtual void mul(Matrix<T> *B,Matrix<T> *Result); // Result = this * B

        virtual void mulScalar(T scale, Matrix<T> *Result); // Rsult = this * scale
        virtual void mulScalar(T scale) { mulScalar(scale,this); } // this *= scale

        virtual void add(Matrix<T> *B,Matrix<T> *Result); // Result = this + B
        virtual void add(Matrix<T> *B) {add(B,this);} // this +=B

        virtual void sub(Matrix<T> *B,Matrix<T> *Result); // Result = this + B
        virtual void sub(Matrix<T> *B) {sub(B,this);} // this -=B


};

#endif
