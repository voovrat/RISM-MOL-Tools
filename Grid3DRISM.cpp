#include "Grid3DRISM.h"

void restrictGrid3DRISM(Grid *src,Grid *result)
{
	Grid3DRISM *goodSrc;
	Grid3DRISM *goodDst;

	goodSrc = dynamic_cast<Grid3DRISM*>(src);
	if(!goodSrc) 
		throw "restictGrid3DRISM: invalid class of src; should be Grid1DRISM";

	goodDst = dynamic_cast<Grid3DRISM*>(result);
	if(!goodDst) 
		throw "restictGrid3DRISM: invalid class of dst; should be Grid1DRISM";	

	goodDst->m_Nx = goodSrc->m_Nx/2;
	goodDst->m_Ny = goodSrc->m_Ny/2;
	goodDst->m_Nz = goodSrc->m_Nz/2;


	goodDst->m_dRx = goodSrc->m_dRx*2;
	goodDst->m_dRy = goodSrc->m_dRy*2;
	goodDst->m_dRz = goodSrc->m_dRz*2;


	goodDst->m_dKx = Grid3DRISM::calcDK(goodDst->m_Nx,goodDst->m_dRx);
	goodDst->m_dKy = Grid3DRISM::calcDK(goodDst->m_Ny,goodDst->m_dRy);
	goodDst->m_dKz = Grid3DRISM::calcDK(goodDst->m_Nz,goodDst->m_dRz);
}

void interpolateGrid3DRISM(Grid *src,Grid *result)
{
	Grid3DRISM *goodSrc;
	Grid3DRISM *goodDst;

	goodSrc = dynamic_cast<Grid3DRISM*>(src);
	if(!goodSrc) 
		throw "interpolateGrid3DRISM: invalid class of src; should be Grid1DRISM";

	goodDst = dynamic_cast<Grid3DRISM*>(result);
	if(!goodDst) 
		throw "interpolateGrid3DRISM: invalid class of dst; should be Grid1DRISM";	

	goodDst->m_Nx = goodSrc->m_Nx*2;
	goodDst->m_Ny = goodSrc->m_Ny*2;
	goodDst->m_Nz = goodSrc->m_Nz*2;

	goodDst->m_dRx = goodSrc->m_dRx/2;
	goodDst->m_dRy = goodSrc->m_dRy/2;
	goodDst->m_dRz = goodSrc->m_dRz/2;

	goodDst->m_dKx = Grid3DRISM::calcDK(goodDst->m_Nx,goodDst->m_dRx);
	goodDst->m_dKy = Grid3DRISM::calcDK(goodDst->m_Ny,goodDst->m_dRy);
	goodDst->m_dKz = Grid3DRISM::calcDK(goodDst->m_Nz,goodDst->m_dRz);
}

void extendGrid3DRISM(Grid *src,Grid *result)
{
	Grid3DRISM *goodSrc;
	Grid3DRISM *goodDst;

	goodSrc = dynamic_cast<Grid3DRISM*>(src);
	if(!goodSrc) 
		throw "extendGrid3DRISM: invalid class of src; should be Grid1DRISM";

	goodDst = dynamic_cast<Grid3DRISM*>(result);
	if(!goodDst) 
		throw "extendGrid3DRISM: invalid class of dst; should be Grid1DRISM";	

	goodDst->m_Nx = goodSrc->m_Nx*2;
	goodDst->m_Ny = goodSrc->m_Ny*2;
	goodDst->m_Nz = goodSrc->m_Nz*2;

	goodDst->m_dRx = goodSrc->m_dRx;
	goodDst->m_dRy = goodSrc->m_dRy;
	goodDst->m_dRz = goodSrc->m_dRz;

	goodDst->m_dKx = Grid3DRISM::calcDK(goodDst->m_Nx,goodDst->m_dRx);
	goodDst->m_dKy = Grid3DRISM::calcDK(goodDst->m_Ny,goodDst->m_dRy);
	goodDst->m_dKz = Grid3DRISM::calcDK(goodDst->m_Nz,goodDst->m_dRz);
}

void generateGridDimension(Real N,Real dR,Real *gridPoints)
{Integer i;
	for(i=0;i<N;i++)
	{
		gridPoints[i] = GAMMA_COORDINATE(N,dR,i);
	}
}

void generateGridKz(Real N,Real dKz,Real *gridPoints)
{Integer i;
	for(i=0;i<N/2+1;i++)
	{
		gridPoints[i] = GAMMA_COORDINATE(N,dKz,i);
	}
}
