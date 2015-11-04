#ifndef linearInterpolation2x_h
#define linearInterpolation2x_h

// inserts 1 new sample between 2 old ones.
// grid step of src -> dx
// grid step of dst -> dx/2
// Ndst = 2Nsrc-1
//gridDst[0] = gridSrc[0]
//gridDst[2Nsrc-2]= gridSrc[Nsrc-1]
//  (2Nsrc-2) -> x0 + 2Nsrc*dx/2 - 2*dx/2
//  (Nsrc-1)  -> x0 + 2Nsrc*dx - dx

template<class T>
inline void linearInterpolation2x(
		T *src,
		Integer Nsrc,
		Integer src_stride,
		T *dst,	//alloced size 2Nsrc-1
		Integer dst_stride
		)
{
	Nsrc--; //Repeat (Nsrc-1) times
	while(Nsrc--)
	{
		*dst = *src;		// dst(x) = src(x)
		dst += dst_stride;	// dst=dst(x+dx/2)
		*dst = (*src + *(src+src_stride))/2;	// dst(x+dx/2)=(src(x) + src(x+dx))/2	
		
		dst+=dst_stride; //dst = dst(x+dx)
		src+=src_stride; //src = src(x+dx)
	}

	*dst = *src;	// dst(x0+(2Nsrc-2)*dx/2 ) = src(x0+(Nsrc-1)dx)
}

#endif
