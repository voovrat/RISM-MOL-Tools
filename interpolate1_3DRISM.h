#ifndef interpolate1_3DRISM_h
#define interpolate1_3DRISM_h

// Nsrc = N
// Ndst = 2N
// gridStepSrc = dx 
// gridStepDst = dx/2
//
// Grid correspondance:
//                                                        *(src+N/2+1)
//                                                          |
//      <------------N/2+1------------>                  <------------N/2-1------>
// src: 0        dx              N/2*dx                  -N/2*dx+dx     .....  -dx
// dst: 0  dx/2  2*dx/2  .....   N*dx/2 (-N*dx/2+dx/2) (-N*dx/2+2*dx/2) ..... -2*dx/2  -dx/2
//      <-------N+1 = 2(N/2+1)-1------>        |        <-------N-3 = 2(N/2-1)-1--->     |
//                                             |           |                             |
//                                          *(dst+N+1)  *(dst+N+2)               (dst+2N-1)    
// (the picture is for src_stride == dst_stride == 1)
//
// Such grid in each direction is used in class Grid3DRISM (see Grid3DRISM.h)
//
// to interpolate such grid one can:
// 1) interpolate two big intervals (0..N/2*dx) and (-N/2*dx+dx .. -dx)
// 2) interpolate two single points (-N/2*dx+dx/2) and (-dx/2)
//
// Note, that interpolation is independent w.r.t dx => let's assume dx==1


template<class T>
void interpolate1_3DRISM
	(	Integer N,
		Integer src_stride,
		Integer dst_stride,
		T *src,
		T *dst	// out, size=2N
	);

#endif
