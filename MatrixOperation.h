#ifndef MatrixOperation_h
#define MatrixOperation_h

#include "Settings.h"

#define MATRIX_OPERATION( fnname, operation )	\
template<class T>				\
inline void fnname (T *dst,			\
		Integer dst_xstep,		\
		Integer dst_ystep,		\
		T *src,				\
		Integer src_xstep,		\
		Integer src_ystep,		\
		Integer xsize,			\
		Integer ysize)			\
{	\
T *pdst,*psrc;			\
Integer i,j;			\
					\
for(	i=0, psrc=src, pdst=dst; 	\
	i<ysize;			\
	i++)				\
{					\
	for(j=0, psrc = src + i*src_ystep, pdst = dst + i*dst_ystep;	\
		j<xsize; 						\
		j++, psrc+=src_xstep, pdst+=dst_xstep)			\
	{							\
		operation;					\
	}							\
}	\
}

MATRIX_OPERATION( copyMatrix , *pdst = *psrc )
MATRIX_OPERATION( addMatrix ,  *pdst += *psrc )
MATRIX_OPERATION( mulMatrixPointwise ,  *pdst *= *psrc )	 
MATRIX_OPERATION( divMatrixPointwise ,  *pdst /= *psrc )

#define SCALAR_MATRIX_OPERATION( fnname, operation )	\
template<class DataType,class ScalarType>				\
inline void fnname (DataType *dst,			\
		Integer dst_xstep,		\
		Integer dst_ystep,		\
		ScalarType scalar,		\
		Integer xsize,			\
		Integer ysize)			\
{	\
DataType *pdst;			\
Integer i,j;			\
					\
for(	i=0, pdst=dst; 	\
	i<ysize;			\
	i++)				\
{					\
	for(j=0, pdst = dst + i*dst_ystep;	\
		j<xsize; 						\
		j++,  pdst+=dst_xstep)			\
	{							\
		operation;					\
	}							\
}	\
}

SCALAR_MATRIX_OPERATION( setMatrixScalar , *pdst = scalar )
SCALAR_MATRIX_OPERATION( addMatrixScalar , *pdst += scalar )
SCALAR_MATRIX_OPERATION( mulMatrixScalar , *pdst *= scalar )	 
SCALAR_MATRIX_OPERATION( divMatrixScalar , *pdst /= scalar )

#endif
