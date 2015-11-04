#ifndef FFTZero3D_h
#define FFTZero3D_h

// FFT and IFFT for functions, which are presented as  f = \sum f_i * \phi_i(r), 
// where \phi_i(r) is a zero-orer spline:  \phi_i(r) = 1,  (m-0.5)\Delta r < r < (m+0.5)\Delta r and 0 otherwise
// The only difference from the FFT: 
//   in FFTZero3D::fft functions are multiplied by sin (k\Delta r/2) / (k \Delta r /2)
//   in FFTZero3D:ifft functions are multiplied by sin (r\Delta k/2) / (r \Delta k /2)

class Grid3DRISM;

#include "Object.h"

#include <complex>

class GridIndex;

//struct compareGrids
//{
//  bool operator()(Grid3DRISM * ,Grid3DRISM *);
//};


class FFTZero3D : public Object
{
protected:
	FFTZero3D() {}
public:
	static FFTZero3D *getInstance()
	{
		static FFTZero3D *instance = NULL;

		if(!instance)
			instance = new FFTZero3D();

		return instance;
	}

	virtual ~FFTZero3D() {}

	//FFTW3DData *findData(Grid3DRISM *grid);
	

	void fft(	Real *in,
			std::complex<Real> *out,
			Grid3DRISM *grid
		);

	void ifft(	std::complex<Real> *in,
			Real *out,
			Grid3DRISM *grid
		);

};


#endif


