#ifndef interpolate3_3DRISM_h
#define interpolate3_3DRISM_h

#include "interpolate1_3DRISM.h"

template<class T>
void interpolate3_3DRISM(
	T *src,
	Integer N, //for 1D interp
	Integer src_stride,
	Integer dst_stride,
	Integer Nrow,
	Integer Ncol,
	Integer src_row_inc, //inside 1 cycle
	Integer src_col_inc, //inside 2 cycles
	Integer dst_row_inc, // inside 1 cycle
	Integer dst_col_inc,  // inside 2 cycles
	T *dst//out
	)
{

Integer row,col;

for(row=0;row<Nrow;row++)
{
	for(col=0;col<Ncol;col++)
	{
		interpolate1_3DRISM<T>(
				N,	//Integer N,
				src_stride,	//Integer src_stride,
				dst_stride,		//Integer dst_stride,
				src,			//T *src,
				dst			//T *dst // out, size=2N
		);

		src+=src_col_inc;
		dst+=dst_col_inc;
	}
	dst+=dst_row_inc; 
	src+=src_row_inc;
}

}


#endif
