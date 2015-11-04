#include "copySubMatrix.h"

template<class T>
void copySubMatrix(	Matrix<T> *src,
			Integer src_row,
			Integer src_col,
			Matrix<T> *dst,
			Integer dst_row,
			Integer dst_col,
			Integer nrow,
			Integer ncol)
{ Integer i,j;
  T tmp;

	for(i=0;i<nrow;i++)
		for(j=0;j<ncol;j++)
		{
			tmp = src->getAt(src_row+i,src_col+j);
			dst->setAt(dst_row+i,dst_col+j,tmp);
		}


}
