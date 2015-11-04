#ifndef Grid3DRISM_h
#define Grid3DRISM_h

#include <math.h>
#include <stdio.h>

#include "Grid.h"
#include "Exception.h"

// class Contain implementation of the Grid class for 1D regular grid.
// it contains: dR, dk,
//
// Class is supposed to contain few members. (e.g. N,dR).

// restrict the fine grid to coarse one. 
  // function does not allocate the memory. 
  // result should be allocated before.
   void restrictGrid3DRISM(Grid *src,Grid *result);

  // restrict the coarse grid to the fine one. 
  // function does not allocate the memory. 
  // result should be allocated before.
   void interpolateGrid3DRISM(Grid *src,Grid *result);

  // extend the grid to the grid with larger cutoff distance. 
  // function does not allocate the memory. 
  // result should be allocated before.
   void extendGrid3DRISM(Grid *src,Grid *result);


class Grid3DRISM : public Grid
{
  protected:
    	Integer m_Nx,m_Ny,m_Nz; // Grid from -N/2*dR..N/2*dR
	Real m_dRx,m_dRy,m_dRz,m_dKx,m_dKy,m_dKz;  

	friend   void restrictGrid3DRISM(Grid *src,Grid *result);
	friend   void interpolateGrid3DRISM(Grid *src,Grid *result);
	friend   void extendGrid3DRISM(Grid *src,Grid *result);

	static Real calcDK(Real N,Real dR)	
	{
		return 2*M_PI / N / dR;
	}

  public:

	Grid3DRISM()
	{}

	Grid3DRISM(Integer Nx,Integer Ny,Integer Nz,Real dRx,Real dRy,Real dRz)
	{
 		m_Nx = Nx;
		m_Ny = Ny;
	  	m_Nz = Nz;

		m_dRx = dRx;
		m_dRy = dRy;
		m_dRz = dRz;

		m_dKx = calcDK(Nx,dRx);
		m_dKy = calcDK(Ny,dRy);
		m_dKz = calcDK(Nz,dRz);		
	}
 
	// copy grid to the given destination.
	// function does not allocate the memory. 
	// result should be allocated before.   
	virtual void copy(Grid *result) const
	{
		Grid3DRISM * r = dynamic_cast<Grid3DRISM *>(result);

		if(!r)
			throw "Gtid3DRISM::copy Invalid type of Grid obj: should be Grid3DRISM";		

 		r->m_Nx = m_Nx;
		r->m_Ny = m_Ny;
		r->m_Nz = m_Nz;
	
		r->m_dRx = m_dRx;
		r->m_dRy = m_dRy;
		r->m_dRz = m_dRz;

		r->m_dKx = m_dKx;
		r->m_dKy = m_dKy;
		r->m_dKz = m_dKz;
	}

	Integer getNx() const	{return m_Nx;}
	Integer getNy() const	{return m_Ny;}
	Integer getNz() const	{return m_Nz;}

	Real getDRx()	const {return m_dRx;}
	Real getDRy()	const {return m_dRy;}
	Real getDRz()	const {return m_dRz;}	

	Integer getNKx() const	{return m_Nx;}
	Integer getNKy() const	{return m_Ny;}
	Integer getNKz() const	{return m_Nz/2+1;}

	Real getDKx()	const {return m_dKx;}	
	Real getDKy()	const {return m_dKy;}	
	Real getDKz()	const {return m_dKz;}	

	virtual Integer isEqual(const Grid *grid) const
	{
		const Grid3DRISM *goodGrid = dynamic_cast<const Grid3DRISM*>(grid);

		if(!goodGrid)
			throw new Exception((Object *)this,"Grid3DRISM::isEqual : Incorrect object class ");
/*	
		printf("Grid3DRISM::isEqual: fabs(1)=%lf\n",fabs(1));
		printf("Grid3DRISM::isEqual: fabs(0)=%lf\n",fabs(0));
		printf("G1: %dx%dx%d %lfx%lfx%lf\n",m_Nx,m_Ny,m_Nz,m_dRx,m_dRy,m_dRz);
		printf("G2: %dx%dx%d %lfx%lfx%lf\n",goodGrid->m_Nx,goodGrid->m_Ny,goodGrid->m_Nz,goodGrid->m_dRx,goodGrid->m_dRy,goodGrid->m_dRz);	
	
		printf("1: Nx=Nx:%d\n",goodGrid->m_Nx==m_Nx );
		printf("2: dRx=dRx:%lf %d\n",fabs(goodGrid->m_dRx-m_dRx),fabs(goodGrid->m_dRx - m_dRx)<1e-6 );
		printf("3: Ny=Ny:%d\n",goodGrid->m_Ny==m_Ny );
		printf("4: dRy=dRy:%lf %d\n",fabs(goodGrid->m_dRy-m_dRy),fabs(goodGrid->m_dRy - m_dRy)<1e-6 );
	printf("5: Nz=Nz:%d\n",goodGrid->m_Nz==m_Nz );
		printf("6: dRz=dRz:%lf %d\n",fabs(goodGrid->m_dRz-m_dRz),fabs(goodGrid->m_dRz - m_dRz)<1e-6 );			
*/
		Integer R = (goodGrid->m_Nx==m_Nx) && (fabs(goodGrid->m_dRx - m_dRx)<1e-6) &&
			(goodGrid->m_Ny==m_Ny) && (fabs(goodGrid->m_dRy - m_dRy)<1e-6) &&
			(goodGrid->m_Nz==m_Nz) && (fabs(goodGrid->m_dRz - m_dRz)<1e-6);

//		printf("R:%d\n",R);

		return R;
//		return	goodGrid->m_Nx==m_Nx && fabs(goodGrid->m_dRx - m_dRx)<1e-6 &&
//			goodGrid->m_Ny==m_Ny && fabs(goodGrid->m_dRy - m_dRy)<1e-6 &&
//			goodGrid->m_Nx==m_Nz && fabs(goodGrid->m_dRz - m_dRz)<1e-6;
	}

  // creates an empty solution of derived class.
  // typical implementation: 
  //  class G: Grid { ... };
  //  G::factory() {return new G;}
   virtual Grid *factory() const
	{
		return new Grid3DRISM(1,1,1,1,1,1);
	}


};

#define GAMMA_FOR(grid)						\
{ Grid3DRISM *GAMMA_FOR_g3d = (Grid3DRISM *)grid;					\
										\
Integer GAMMA_FOR_Nx = GAMMA_FOR_g3d->getNx();					\
Integer GAMMA_FOR_Ny = GAMMA_FOR_g3d->getNy();					\
Integer GAMMA_FOR_Nz = GAMMA_FOR_g3d->getNz();					\
										\
Real GAMMA_FOR_dRx = GAMMA_FOR_g3d->getDRx();					\
Real GAMMA_FOR_dRy = GAMMA_FOR_g3d->getDRy();					\
Real GAMMA_FOR_dRz = GAMMA_FOR_g3d->getDRz();					\
										\
Integer GAMMA_FOR_i;								\
Integer GAMMA_FOR_j;								\
Integer GAMMA_FOR_k;								\
for(GAMMA_FOR_i=0;GAMMA_FOR_i<GAMMA_FOR_Nx;GAMMA_FOR_i++)			\
for(GAMMA_FOR_j=0;GAMMA_FOR_j<GAMMA_FOR_Ny;GAMMA_FOR_j++)			\
for(GAMMA_FOR_k=0;GAMMA_FOR_k<GAMMA_FOR_Nz;GAMMA_FOR_k++)			\
{

#define END_GAMMA_FOR  } }

#define GAMMA_COORDINATE(N,dR,counter)  \
		  ( ( counter<=N/2) ?	\
		      counter*dR :    	\
		  ( counter - N )*dR )

#define GAMMA_FOR_X GAMMA_COORDINATE(GAMMA_FOR_Nx,GAMMA_FOR_dRx,GAMMA_FOR_i)
#define GAMMA_FOR_Y GAMMA_COORDINATE(GAMMA_FOR_Ny,GAMMA_FOR_dRy,GAMMA_FOR_j)
#define GAMMA_FOR_Z GAMMA_COORDINATE(GAMMA_FOR_Nz,GAMMA_FOR_dRz,GAMMA_FOR_k)

#define GAMMA_FOR_R sqrt(	GAMMA_FOR_X * GAMMA_FOR_X + \
				GAMMA_FOR_Y * GAMMA_FOR_Y + \
				GAMMA_FOR_Z * GAMMA_FOR_Z   \
			)

void generateGridDimension(Real N,Real dR,Real *gridPoints);


#define KGAMMA_FOR(grid)							\
Grid3DRISM *KGAMMA_FOR_g3d = (Grid3DRISM *)grid;				\
										\
Integer KGAMMA_FOR_Nx = KGAMMA_FOR_g3d->getNx();					\
Integer KGAMMA_FOR_Ny = KGAMMA_FOR_g3d->getNy();					\
Integer KGAMMA_FOR_Nz = KGAMMA_FOR_g3d->getNz();					\
Integer KGAMMA_FOR_Nz2 = KGAMMA_FOR_Nz/2 + 1;					\
										\
Real KGAMMA_FOR_dKx = KGAMMA_FOR_g3d->getDKx();				\
Real KGAMMA_FOR_dKy = KGAMMA_FOR_g3d->getDKy();				\
Real KGAMMA_FOR_dKz = KGAMMA_FOR_g3d->getDKz();				\
										\
Integer KGAMMA_FOR_i;								\
Integer KGAMMA_FOR_j;								\
Integer KGAMMA_FOR_k;								\
for(KGAMMA_FOR_i=0;KGAMMA_FOR_i<KGAMMA_FOR_Nx;KGAMMA_FOR_i++)			\
for(KGAMMA_FOR_j=0;KGAMMA_FOR_j<KGAMMA_FOR_Ny;KGAMMA_FOR_j++)			\
for(KGAMMA_FOR_k=0;KGAMMA_FOR_k<KGAMMA_FOR_Nz2;KGAMMA_FOR_k++)			\
{

#define END_KGAMMA_FOR  }

#define KGAMMA_COORDINATE(N,dK,counter)   GAMMA_COORDINATE(N,dK,counter)

#define KGAMMA_FOR_KX GAMMA_COORDINATE(KGAMMA_FOR_Nx,KGAMMA_FOR_dKx,KGAMMA_FOR_i)
#define KGAMMA_FOR_KY GAMMA_COORDINATE(KGAMMA_FOR_Ny,KGAMMA_FOR_dKy,KGAMMA_FOR_j)
#define KGAMMA_FOR_KZ GAMMA_COORDINATE(KGAMMA_FOR_Nz,KGAMMA_FOR_dKz,KGAMMA_FOR_k)

#define KGAMMA_FOR_KR sqrt(	KGAMMA_FOR_KX * KGAMMA_FOR_KX + \
				KGAMMA_FOR_KY * KGAMMA_FOR_KY + \
				KGAMMA_FOR_KZ * KGAMMA_FOR_KZ   \
			)


inline void generateGridKx(Real N,Real dK,Real *gridPoints)
{
	generateGridDimension(N,dK,gridPoints);
}

inline void generateGridKy(Real N,Real dK,Real *gridPoints)
{
	generateGridDimension(N,dK,gridPoints);
}

void generateGridKz(Real N,Real dKz,Real *gridPoints);


inline Integer getIndexFromCoordinate(	Real coordinate, 
					Integer N,
					Real dR)
{


	Integer K = (coordinate>=0) 	? (Integer) (coordinate / dR + 0.5)
				 	: (Integer) (coordinate / dR- 0.5);

//	printf("X = %lf, X/dR = %lf -> %ld\n",coordinate,coordinate/dR,K);

	return (K>=0) ? K : K+N;
}

#define GRID3DRISM_BAD_INDEX	-1 

inline Integer getXYZOffset(	Real x,
				Real y,
				Real z,
				Grid3DRISM *grid
			)
{
	Integer Nx = grid->getNx();
	Integer Ny = grid->getNy();
	Integer Nz = grid->getNz();

	Integer x_index = getIndexFromCoordinate( x, Nx, grid->getDRx());
	Integer y_index = getIndexFromCoordinate( y, Ny, grid->getDRy());
	Integer z_index = getIndexFromCoordinate( z, Nz, grid->getDRz());
	
	if (	x_index>=0 && x_index < Nx &&
		y_index>=0 && y_index < Ny &&
		z_index>=0 && z_index < Nz 
	)
		return 	x_index * Ny * Nz +
			y_index * Nz +
			z_index;
	else
		return GRID3DRISM_BAD_INDEX;
}

inline Integer getKxKyKzOffset(	Real kx,
				Real ky,
				Real kz,
				Grid3DRISM *grid
			)
{
	Integer Nx = grid->getNx();
	Integer Ny = grid->getNy();
	Integer Nz = grid->getNz();

	Integer NKz = Nz/2+1;

	Integer x_index = getIndexFromCoordinate( kx, Nx, grid->getDKx());
	Integer y_index = getIndexFromCoordinate( ky, Ny, grid->getDKy());
	Integer z_index = getIndexFromCoordinate( kz, Nz, grid->getDKz());
	
	if (	x_index>=0 && x_index < Nx &&
		y_index>=0 && y_index < Ny &&
		z_index>=0 && z_index < NKz 
	)
		return 	x_index * Ny * NKz +
			y_index * NKz +
			z_index;
	else
		return GRID3DRISM_BAD_INDEX;


}





#endif
