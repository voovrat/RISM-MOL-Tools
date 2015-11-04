#include <stdio.h>
#include <stdlib.h>

#include <list>

#include "Exception.h"
#include "readGrid.h"
#include "Grid3DRISM.h"
#include "readDoubleTableSimple.h"
#include "readCoorFile.h"
#include "AtomRecord.h"
#include "atomlist2coors.h"
#include "rotationMatrix.h"
#include "mulMatrix.h"
#include "Units.h"
#include "getMaxDistance.h"
#include "isLocalMax.h"

main(int argc,char *argv[])
{
try{

if(argc<4)
{
	puts("Usage: createBindingMoleculesXYZ solvent.xyz gridPrefix gmaxPrefix treshold [out.xyz]");
	return 1;
}

const char *solventFile = argv[1];
const char *gridPrefix = argv[2];
const char *gmaxPrefix = argv[3];
Real treshold = strtod(argv[4],NULL);

FILE *fout;

if(argc>5)
{
	fout = fopen(argv[5],"w");
}
else
	fout = stdout;

char fname[256];

Grid3DRISM grid;

readGrid(	gridPrefix,	//const char *prefix,
		&grid	//Grid3DRISM *grid
	);

Integer N = grid.getNx() * grid.getNy() * grid.getNz();

Real *Gmax;;
Real *PhiMax;
Real *ThetaMax;
Real *PsiMax;

Integer nlin,ncol;

#define READ_DISTRIBUTION(Name)   \
sprintf(fname,"%s_" #Name ".3d",gmaxPrefix); \
readDoubleTableSimple(	fname,	/*const char *fname,*/ \
			&nlin,	/*Integer *nlin,	//out*/ \
			&ncol,	/*Integer *ncol,	//out*/ \
			&Name	/*Real **result //out, will be allocated*/\
			); \
if(nlin!=N) throw "Number of lines in " #Name " file is inconsistent with the grid";

READ_DISTRIBUTION(Gmax)
READ_DISTRIBUTION(PhiMax)
READ_DISTRIBUTION(PsiMax)
READ_DISTRIBUTION(ThetaMax)

#undef READ_DISTRIBUTION

std::list<AtomRecord> solventAtoms;

readCoorFile(	solventFile,	//const char *file,
		&solventAtoms	//std::list<AtomRecord> *records
	);

Integer Nsites = solventAtoms.size();
Real *coors = (Real *)malloc( Nsites * 3 * sizeof(Real) );

atomlist2coors(	&solventAtoms,	//std::list<AtomRecors> *atomlist,
		coors	//		Real *coors //Nsites * 3 real array
		);

std::list<AtomRecord> outlist;

Real Rot[9];

Real *rotatedCoors = (Real *)malloc( Nsites * 3 * sizeof(Real));

Real *pGmax = Gmax;
Real *pPhiMax = PhiMax;
Real *pThetaMax = ThetaMax;
Real *pPsiMax = PsiMax;

Real kAngstr = Units::distanceUnits()->unit2unit("Bohr","Angstr");
Real x0,y0,z0;

Real R0 = getMaxDistance(	coors,	//Real *coors,	//N*3
				Nsites	//Integer N
			);

GAMMA_FOR(&grid)
{
	if(	*pGmax > treshold)	 
	{
		
		x0 = GAMMA_FOR_X * kAngstr;		
		y0 = GAMMA_FOR_Y * kAngstr;
		z0 = GAMMA_FOR_Z * kAngstr;

	
		if( isLocalMax(	Gmax,	//Real *data,	
				&grid,	//Grid3DRISM *grid,
				x0 / kAngstr,	//Real x0,
				y0 / kAngstr,	//Real y0,
				z0 / kAngstr,	//Real z0,
				R0 / kAngstr	//Real radius 
				)
		)
		{


		rotationMatrix(	*pPsiMax,	//double psi,
				*pThetaMax,	//double theta,
				*pPhiMax,	//double phi,
				Rot	//double *result // 3x3 matrix, xstep=1, ystep=3
			);

		 mulMatrix( 
			Rot,	//double *A, // MxN
			1,	//int A_xstep, 
			3,	//int A_ystep,	
			coors,	//double *B, //NxK 
			3,	//int B_xstep,
			1,	//int B_ystep,
			3,	//int M, 	
			3,	//int N,
			Nsites,	//int K,
			rotatedCoors,	//double *result, // MxK
			3,	//int result_xstep,
			1	//int result_ystep
		);
		
		std::list<AtomRecord>::iterator it;
		Real *XYZ;
		for( 	it = solventAtoms.begin(), XYZ = rotatedCoors;
			it != solventAtoms.end();
			it++, XYZ+=3 )
		{
			AtomRecord a;
			strcpy(a.element,(*it).element);
			a.x = XYZ[0] + x0;
			a.y = XYZ[1] + y0 ;
			a.z = XYZ[2] + z0;

			outlist.push_back(a);
		} //for

		}// if isLocalMax
	}// is *pGmax > threshold
	pGmax++;
	pPhiMax++;
	pThetaMax++;
	pPsiMax++;	
}
END_GAMMA_FOR

// write output 

fprintf(fout,"%d\n",(int)outlist.size());
fprintf(fout,"Solvent molecules %s for %s, treshold=%lf\n",solventFile,gridPrefix,treshold);

std::list<AtomRecord>::iterator it;
for(it=outlist.begin(); it!=outlist.end(); it++)
{
	fprintf(fout,"%s %10.3g %10.3g %10.3g\n", (*it).element,(*it).x,(*it).y,(*it).z);
}


free(rotatedCoors);
free(coors);

free(Gmax);
free(PhiMax);
free(ThetaMax);
free(PsiMax);

} catch ( Exception *e ) {
	printf("Exception: %s\n",e->toString());
} catch ( const char *str ) {
	printf("Exception: %s\n",str);
}

return 0;
}
