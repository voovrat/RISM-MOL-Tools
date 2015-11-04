#ifndef ArrayOperations_h
#define ArrayOperations_h

#include <string.h>
#include <math.h>

template<class DataType>
inline void copyArray(DataType *dst,DataType *src,Integer N)
{
	memcpy(dst,src,N*sizeof(DataType));
}

#define BinaryArrayOperation(fnname,operation)	\
template<class DataType>			\
inline void fnname(DataType *dst,DataType *src,Integer N)	\
{	while(N--)				\
	{					\
	operation;				\
	dst++; src++; 				\
	}					\
}

BinaryArrayOperation( addArray, *dst += *src )
BinaryArrayOperation( subArray, *dst -= *src )
BinaryArrayOperation( mulArray, *dst *= *src )
BinaryArrayOperation( divArray, *dst /= *src )

#define ScalarArrayOperation(fnname,operation)	\
template<class DataType,class ScalarType>	\
inline void fnname(DataType *dst,ScalarType scalar,Integer N)\
{	while(N--)				\
	{					\
	operation;				\
	dst++;  				\
	}					\
}


ScalarArrayOperation(  setArrayScalar, *dst = scalar )
ScalarArrayOperation(  addArrayScalar, *dst += scalar ) 
ScalarArrayOperation(  subArrayScalar, *dst -= scalar )
ScalarArrayOperation(  subScalarArray, *dst = scalar - *dst )
ScalarArrayOperation(  mulArrayScalar, *dst *= scalar )
ScalarArrayOperation(  divArrayScalar, *dst /= scalar )
ScalarArrayOperation(  divScalarArray, *dst = scalar / *dst )


#define UnaryArrayOperation(fnname,operation)	\
template<class DataType>			\
void fnname(DataType *dst,Integer N)		\
{	while(N--)				\
	{					\
	operation;				\
	dst++;  				\
	}					\
}

UnaryArrayOperation( expArray,  *dst = exp(*dst) )
UnaryArrayOperation( logArray,  *dst = log(*dst) )
UnaryArrayOperation( sqrtArray, *dst = sqrt(*dst) ) 

#endif
