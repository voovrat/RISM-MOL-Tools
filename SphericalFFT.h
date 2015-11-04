#ifndef SphericalFFT_h
#define SphericalFFT_h

#include "Object.h"
#include <complex>


class Grid1DRISM;
class GridIndex;

class SphericalFFT : public Object
{
protected: 

	GridIndex *m_gridIndex;
	static SphericalFFT *m_instance;

public:
	SphericalFFT();

	static SphericalFFT *getInstance();
	virtual ~SphericalFFT();


	// return 1
	Real	d3fft(	Real *in,
			Real *out,
			Grid1DRISM *grid
		);

	//return 1
	Real d3ifft(	Real *in,
			Real *out,
			Grid1DRISM *grid
		);

	void 	dst(	Real *in,
			Real *out,
			Grid1DRISM *grid
		   );

};


#endif


