#ifndef copySubMatrix_h
#define copySubMatrix_h

#include "Matrix.h"

template<class T>
void copySubMatrix(	Matrix<T> *src,
			Integer src_row,
			Integer src_col,
			Matrix<T> *dst,
			Integer dst_row,
			Integer dst_col,
			Integer nrow,
			Integer ncol);
	

#endif
