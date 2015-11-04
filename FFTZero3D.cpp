#include "FFTZero3D.h"
#include "FFTW3D.h"
#include "Grid3DRISM.h"

#include "sinc.h"

void FFTZero3D::fft(	Real *in,
		std::complex<Real> *out,
		Grid3DRISM *grid
	)
{
FFTW3D *fftw = FFTW3D::getInstance();

Real kfft =
fftw->fft(	in,	//Real *in,
		out,	//std::complex<Real> *out,
		grid	//Grid3DRISM *grid
	);

std::complex<Real> *ptr=out;
Real argx,argy,argz;
Real dx2 = grid->getDRx()/2;
Real dy2 = grid->getDRy()/2;
Real dz2 = grid->getDRz()/2;
KGAMMA_FOR(grid)
{
	argx = KGAMMA_FOR_KX * dx2;
	argy = KGAMMA_FOR_KY * dy2;
	argz = KGAMMA_FOR_KZ * dz2;

	*ptr *= sinc(argx)*sinc(argy)*sinc(argz) * kfft;		

	ptr++;
}
END_KGAMMA_FOR


}

void FFTZero3D::ifft(	std::complex<Real> *in,
		Real *out,
		Grid3DRISM *grid
	)
{
FFTW3D *fftw = FFTW3D::getInstance();

Real kfft = 
fftw->ifft(	in,	//std::complex<Real> *in
		out,	//Real *out,
		grid	//Grid3DRISM *grid
	);

Real *ptr=out;
Real argx,argy,argz;
Real dx2 = grid->getDKx()/2;
Real dy2 = grid->getDKy()/2;
Real dz2 = grid->getDKz()/2;
GAMMA_FOR(grid)
{
	argx = GAMMA_FOR_X * dx2;
	argy = GAMMA_FOR_Y * dy2;
	argz = GAMMA_FOR_Z * dz2;

	*ptr *= sinc(argx)*sinc(argy)*sinc(argz) * kfft;		

	ptr++;
}
END_GAMMA_FOR


}


