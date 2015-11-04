#include "buildSphericalK3.h"

#include "UnaryFunction.h"
#include <complex>
#include "Grid3DRISM.h"

#include <math.h>

// ResultType shuld be convertable to complex<Real>
// That's because one may have Real-valued function, which one want to represent as complex-valued

template<class ResultType>
void buildSphericalK3(	UnaryFunction<Real,ResultType> *fn,
			Grid3DRISM *grid,
			std::complex<Real> *data3D,		// out
			Real drDivider  	
		)
{

Real kx_step = grid->getDKx() / drDivider;
Real ky_step = grid->getDKy() / drDivider;
Real kz_step = grid->getDKz() / drDivider;

Real kx,ky,kz;
Real kr;
Real KmaxX = grid->getDKx() * grid->getNx()/2;
Real KmaxY = grid->getDKy() * grid->getNy()/2;
Real KmaxZ = grid->getDKz() * grid->getNz()/2;

Integer offset;

Real dV = kx_step*ky_step*kz_step / grid->getDKx() / grid->getDKy() / grid->getDKz();

Integer start = -(drDivider/2);

Integer MaxOffset = grid->getNKx() * grid->getNKy() * grid->getNKz();

Real KMaxR = KmaxX;

if( KMaxR > KmaxY) KMaxR = KmaxY;
if( KMaxR > KmaxZ) KMaxR = KmaxZ;

for(kx = start*kx_step; kx<=KmaxX; kx+=kx_step)
{
	for(ky = start*ky_step; ky<=KmaxY; ky+=ky_step)
	{
		for(kz = start*kz_step; kz<=KmaxZ; kz+=kz_step)
		{
			kr = sqrt(kx*kx + ky*ky + kz*kz);

		//	if(kr>KMaxR) continue;

			offset = getKxKyKzOffset(	kx,	//Real kx,
							ky,	//Real ky,
							kz,	//Real kz,
							grid	//Grid3DRISM *grid
						);

			ResultType value = (*fn)(kr) * dV;

			if(offset>=0) 	data3D[offset] += value;

		}//kz
	}//ky

}//kx

// reflect to the negative values

std::complex<Real> original;

Integer offset_reflectX,offset_reflectY, offset_reflectXY;


for(kx=0; kx<=KmaxX ; kx+=grid->getDKx()/2)
{
	for(ky=0;ky<=KmaxY ;ky+=grid->getDKy()/2)
	{
		for(kz=0;kz<=KmaxZ ; kz+=grid->getDKz()/2)
		{
			kr = sqrt(kx*kx + ky*ky + kz*kz);
		//	if(kr>KMaxR) continue;

			offset = getKxKyKzOffset(	kx,	//Real kx,
							ky,	//Real ky,
							kz,	//Real kz,
							grid	//Grid3DRISM *grid
						);
			if(offset <0 ) continue;		


			original = data3D[offset];
	
			offset_reflectX = getKxKyKzOffset(	-kx,	//Real kx,
								ky,	//Real ky,
								kz,	//Real kz,
								grid	//Grid3DRISM *grid
							);

			offset_reflectY = getKxKyKzOffset(	kx,	//Real kx,
								-ky,	//Real ky,
								kz,	//Real kz,
								grid	//Grid3DRISM *grid
							);
			offset_reflectXY = getKxKyKzOffset(	-kx,	//Real kx,
								-ky,	//Real ky,
								kz,	//Real kz,
								grid	//Grid3DRISM *grid
							);

			if(offset_reflectX>=0) data3D[offset_reflectX] = original;
			if(offset_reflectY>=0) data3D[offset_reflectY] = original;
			if(offset_reflectXY>=0) data3D[offset_reflectXY] = original;
			
		}//kz
	}//ky

}//kx


}


