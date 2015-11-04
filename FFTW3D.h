#ifndef FFTW3D_h
#define FFTW3D_h

class Grid3DRISM;

#include "Object.h"

#include <map>
#include "fftw3.h"
#include <complex>

class GridIndex;

//struct compareGrids
//{
//  bool operator()(Grid3DRISM * ,Grid3DRISM *);
//};


class FFTW3D : public Object
{
protected: 
//	typedef std::map<Grid3DRISM *,FFTW3DData *, compareGrids> DATA_MAP;
//	typedef std::map<Grid3DRISM *,FFTW3DData *, compareGrids>::iterator DATA_MAP_ITERATOR;
//
//	DATA_MAP m_dataMap;
	GridIndex *m_gridIndex;

	static FFTW3D *m_instance;

public:
	FFTW3D();

	static FFTW3D *getInstance();

	virtual ~FFTW3D();

	//FFTW3DData *findData(Grid3DRISM *grid);
	

	// return a sacling coefficient: dRx*dRy*dRz
	Real fft(	Real *in,
			std::complex<Real> *out,
			Grid3DRISM *grid
		);

	//return a scaling coefficient  1/Nx/Ny/Nz/dRx/dRy/dRz
	Real ifft(	std::complex<Real> *in,
			Real *out,
			Grid3DRISM *grid
		);

};


#endif


