#include "buildPotential4.h"

#include "MoleculeCoordinates.h"
#include "SiteSitePotential.h"
#include "Solution3DRISMR.h"

#include <math.h>

#include <stdlib.h>
#include <string.h>

#include "buildPotential.h"

// Peaks of RDFs are preserved

void buildPotential4 (
	MoleculeCoordinates *soluteCoors,
	SiteSitePotential *siteSitePotential,
	Real beta,
	Solution3DRISMR *potential, // output
	Integer divider
)
{




if(!potential->getData())
	potential->createGamma();

Integer soluteSite, solventSite;
Integer NSolventSites = siteSitePotential->getNumSolventSites();
Integer NSoluteSites = siteSitePotential->getNumSoluteSites();

Grid3DRISM *grid = (Grid3DRISM *)potential->getGrid();

Integer Nx = grid->getNx();
Integer Ny = grid->getNy();
Integer Nz = grid->getNz();

Real dx = grid->getDRx();
Real dy = grid->getDRy();
Real dz = grid->getDRz();


if(dx<MIN_DR && dy<MIN_DR && dz<MIN_DR) // it may take too much time to refine the fine enough potentials...
{
 buildPotential (
	soluteCoors,		//MoleculeCoordinates *soluteCoors,
	siteSitePotential,	//SiteSitePotential *siteSitePotential,
	potential		//Solution3DRISMR *potential, // output
);
return;	

}


Real step_x = dx/divider;
Real step_y = dy/divider;
Real step_z = dz/divider;

Real halfCellX = divider/2*step_x;
Real halfCellY = divider/2*step_y;
Real halfCellZ = divider/2*step_z;
 

Real Xmax = (Nx/2)*dx;
Real Xmin = (-Nx/2+1)*dx; 

Real Ymax = (Ny/2)*dy ;
Real Ymin = (-Ny/2+1)*dy ;

Real Zmax = (Nz/2)*dz ;
Real Zmin = (-Nz/2 + 1)*dz;

Real dV = 1.0 / (divider * divider * divider);

Integer offset;
Real x,y,z;
Real x0,y0,z0;
Real Mul,Mul2,Mul6,Mul12;

potential->setZero();

//Real *S = (Real *)malloc( Nx*Ny*Nz*sizeof(Real) );

Real U_treshold = -1/beta * log(G_TRESHOLD); // exp(-betaU)=1e-6 -> U=-1/beta*log(1e-6);

Real U1;
Real Sum;
Real MinU;
Integer inside;
Real *Umap = (Real*)malloc((divider+2)*(divider+2)*(divider+2)*sizeof(Real));

for(solventSite = 0; solventSite < NSolventSites; solventSite++)
{
	//GAMMA_FOR_SOLUTION(potential,solventSite)
	//{

	//memset(S,0,Nx*Ny*Nz*sizeof(Real));

	Real *data = potential->getGamma()[solventSite];
	
//	for( x0= Xmin; x0<=Xmax; x0+=dx )
//	for( y0= Ymin; y0<=Ymax; y0+=dy )
//	for( z0= Zmin; z0<=Zmax; z0+=dz )
	offset = 0;
	GAMMA_FOR(grid)
	{

	
		//offset = getXYZOffset(	x0,		//Real x,
		//			y0,		//Real y,
		//			z0,		//Real z,
		//			grid		//Grid3DRISM *grid
		//			);
	 	
		//if(offset<0) continue;

		x0 = GAMMA_FOR_X;
		y0 = GAMMA_FOR_Y;
		z0 = GAMMA_FOR_Z;

		Real U=0;
		Real MinR = 10000;

		for(soluteSite=	0; soluteSite <NSoluteSites; soluteSite++)
		{
			Real shiftx = x0 - soluteCoors->getX()[soluteSite];
			Real shifty = y0 - soluteCoors->getY()[soluteSite];
			Real shiftz = z0 - soluteCoors->getZ()[soluteSite];
		
			Real R = sqrt(shiftx*shiftx + shifty*shifty + shiftz*shiftz);

			if(R<MinR) MinR = R;

			U1= siteSitePotential->calculatePotential(
					soluteSite, 
					solventSite,
					R) 
					;

			if(U1>BIG_POT) U1=BIG_POT;
			if(U1<-BIG_POT) U1 = - BIG_POT;
			U+=U1;
		} // soluteSite

		

		if(MinR> COARSE_POT_CUT || U>U_treshold ) 
//		if(1)
		{	data[offset]=U;
		//	S[offset]++;
			offset++;
			continue;
		}
		

		int i,j,k;
		Sum=0;
		MinU = BIG_POT;
		inside = 0;
		for(x=x0-halfCellX-step_x,i=0; i<divider+2;  x+=step_x,i++)
		for(y=y0-halfCellY-step_y,j=0; j<divider+2; y+=step_y,j++)
		for(z=z0-halfCellZ-step_z,k=0; k<divider+2; z+=step_z,k++)		
		{

		U=0;
		for(soluteSite=	0; soluteSite <NSoluteSites; soluteSite++)
		{
			Real shiftx = x - soluteCoors->getX()[soluteSite];
			Real shifty = y - soluteCoors->getY()[soluteSite];
			Real shiftz = z - soluteCoors->getZ()[soluteSite];
		
			Real R = sqrt(shiftx*shiftx + shifty*shifty + shiftz*shiftz);

		//	if(R<MinR) MinR = R;
			U1= siteSitePotential->calculatePotential(
					soluteSite, 
					solventSite,
					R) 
					;

			if(U1>BIG_POT) U1=BIG_POT;
			if(U1<-BIG_POT) U1 = - BIG_POT;
			U+=U1;


		} // soluteSite

		Umap[ (i*(divider+2) + j)*(divider+2) + k ] = U;
		if(U<MinU) 
		{
			MinU=U;

		}
		inside =(i>0) && (i<divider+1) && 
			(j>0) && (j<divider+1) && 
			(k>0) && (k<divider+1);
	

		if(inside) Sum+=U;
		// Mul   = (exp(-beta*U)-1);
		// Mul2 = Mul*Mul*Mul*Mul;
		// Mul6 = Mul2*Mul2*Mul2;
		// Mul12 = Mul6*Mul6;

		//if(Mul12>BIG_POT) Mul12=BIG_POT;


		//if(U>1) Mul12 = 1/BIG_POT;
	
		
		//data[offset]+=U*Mul12 ;
		//S[offset]+=Mul12;

		}//sub xyz


		Integer divider2 = (divider+2)*(divider+2);
		Integer LocMinCount=0;
		Real LocMinU =0;
		Integer loc_offset;
		for(i=1; i<divider+1; i++)
		for(j=1; j<divider+1; j++)
		for(k=1; k<divider+1; k++)
		{
			loc_offset = (i*(divider+2) + j)*(divider+2) + k;

			if( 	(Umap[loc_offset]<Umap[loc_offset+divider2] && // in x direction
				Umap[loc_offset]<Umap[loc_offset-divider2] ) 
				|| 
				(Umap[loc_offset]<Umap[loc_offset+divider+2] && // in y direction
				Umap[loc_offset]<Umap[loc_offset-divider-2] ) 
				||
				(Umap[loc_offset]<Umap[loc_offset+1] && // in z direction
				 Umap[loc_offset]<Umap[loc_offset-1] ) 
			)
			{
				LocMinCount++;
				LocMinU +=Umap[loc_offset];
			}


		}


		if(LocMinCount>0) data[offset]=LocMinU/LocMinCount;
		else data[offset]=Sum/(divider*divider*divider);
	


		//data[offset]+=exp(-beta*U)*dV;
	offset++;
	}//xyz
	END_GAMMA_FOR

//	Integer N = Nx*Ny*Nz;
//	Real *ptrData = data;
//	Real *ptrS = S;
//	while(N--)
//	{
//		if(*ptrS>0) *ptrData /= *ptrS;
//		ptrData++;
//		ptrS++;
//	} 


}//for solventSite

//free(S);
free(Umap);

}
