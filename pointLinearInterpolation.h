#ifndef pointLinearInterpolation_h
#define pointLinearInterpolation_h

// returns the function value in poInteger x2, then values in x0 and x1 are given.
// Uses:
//   (x1-x0)/(x2-x0) = (f1-f0)/(f2-f0) =>
//   
//  f2 = f0 + (x2-x0)/(x1-x0) * (f1-f0);
// 
// where  f0= f(x0), f1=f(x1), f2=f(x2)
//

template<class GridT, class ValueT>
inline ValueT pointLinearInteroplation(	
	GridT x0,
	ValueT f0,
	GridT x1,
	ValueT f1,
	GridT  x2
	)
{
	return f0 + (x2-x0)/(x1-x0)*(f1-f0);
}


#endif
