#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <string>

#include "Settings.h"
#include "Exception.h"
#include "readDoubleTableSimple.h"
#include "openOrDie.h"
#include "readStrings.h"
#include "Grid3DRISM.h"
#include "readGrid.h"
#include "calculateLocalG.h"
#include "writeDoubleArrayToFile.h"
#include "ArrayOperations.h"
#include "Units.h"
#include "rotationMatrix.h"
#include "mulMatrix.h"
#include "findProbableGmaxRegions.h"
#include "getMaxDistance.h"
#include "RotatedCoorsTable.h"
#include "readCoorFile.h"
#include "atomlist2coors.h"

#include "getPath.h"
#include "searchInPath.h"

// 1) instead of calculationg convolutions just "calculateLocalG" (test rotation in the point)
// 2) use treshold to find areas, where exist i: g[i]>Threshold
// 3) filter these areas with smooting filter (ball) of molecule size -> 
// these are the probable molecule positions (other positions are not checked)

main(int  argc,char *argv[])
{
char Error[256];

try{




	if(argc<=5)
	{
		puts("Usage: getBestRotations: solvent.xyz distributionFiles.txt gridPrefix outputPrefix threshold [Nrotations=10] [Nrefinements=5]");
	return 1;
	}

	Integer Nrotations = 10;
	Integer Nrefinments = 5;

	Real treshold = strtod(argv[5],NULL);

	if(treshold <= 0)
	{
		sprintf(Error,"Invalid treshold: %g",treshold);
		throw Error;
	}

	if(argc>6)
	{
		Nrotations = (int)strtod(argv[6],NULL);
	}	

	if(argc>7)
	{
		Nrefinments = (int)strtod(argv[7],NULL);
	}


	char *gridPrefix = argv[3];
	char *outputPrefix = argv[4];

	Integer nlin,ncol;
		
	printf("reading solvent coordinates...\n");
//	readDoubleTableSimple(	argv[1],//const char *fname,
//				&nlin,	//Integer *Nrow,	//out
//				&ncol,	//Integer *Ncol,	//out
//				&coors	//Real **result //out, will be allocated
//			);
	
	


	std::list<AtomRecord> atomlist;
	readCoorFile(	argv[1],	//const char *file,
			&atomlist	//std::list<AtomRecord> *records
			);

	Integer Nsites = atomlist.size();

	Real *coors = (Real *)malloc( Nsites * 3 * sizeof(Real) );
	
	atomlist2coors(	&atomlist,	//std::list<AtomRecord> *atomlist,
			coors	//Real *coors //Nsites * 3 real array
			);
	
	int i;
	Real kUnit = Units::distanceUnits()->unit2unit("Angstr","Bohr");
	for(i=0;i<Nsites*3;i++) coors[i]*=kUnit;

	FILE *fdistr = openOrDie(argv[2]);
	std::list<std::string> distributionFiles;
	
	printf("printf read distribution files list...\n");
	readStrings(	fdistr,	//FILE *f,
			&distributionFiles	//std::list<std::string> *strings,
			//int trimStrings=1,	// remove spaces from begin/end
			//int removeEmptyStrings=1 //boolean
		);

	fclose(fdistr);

	if(Nsites!=distributionFiles.size())
		throw "Number of non-zero lines in distribution file should be the same as number of atoms in solvent coordinates file";

//	Integer Nsites = nlin;
	
	Grid3DRISM grid;
	printf("reading grid files...\n");
	readGrid(	gridPrefix,	//const char *prefix,
			&grid	//Grid3DRISM *grid
		);

	Integer N = grid.getNx() * grid.getNy() * grid.getNz();
	Real *g_data = (Real *)malloc( N * Nsites * sizeof(Real) );
	Real **g_index 	= (Real **)malloc( Nsites * sizeof(Real*) );

	Integer site;
	Real *ptr;
	for(site=0, ptr=g_data; site<Nsites; site++, ptr+=N )
	{
		g_index[site] = ptr;
	}
	

	Real *data;
	
	std::list<std::string>::iterator it;
	for(	it = distributionFiles.begin(), site=0; 
		it != distributionFiles.end();
		it++, site++)
	{
		printf("reading %s\n",(*it).c_str());
		readDoubleTableSimple(	
			(*it).c_str(),	//const char *fname,
			&nlin,	//Integer *Nrow,	//out
			&ncol,	//Integer *Ncol,	//out
			&data	//Real **result //out, will be allocated
			);
		if( nlin != N)
			throw "Number of lines in distribution file is inconsistent with grid";

		memcpy(	g_index[site],	//void *dest, 
			data,		//const void *src, 
			N * sizeof(Real)	//size_t n
			);	

		free(data);
	}

	printf("finding the most probable area...\n");	

	Real R = getMaxDistance(
			coors,	//Real *coors,	//N*3
			Nsites	//Integer N
			);

	Integer *probableGmax = (Integer *)malloc( N * sizeof(Integer) );
	
	findProbableGmaxRegions(g_index,	//Real **g_index, // array of g functions
				&grid,	//Grid3DRISM *grid,
				Nsites,	//Integer Nsites,	// number of g functions
				treshold,	//Real treshold,	
				R,	//Real radius,	// radius of the filter (typically: max distance between the molecule's atoms )
				probableGmax	//Integer *probableGmax //out (is not allocated)
				);	


	printf("building the table of rotations...\n");

	RotatedCoorsTable rotatedCoorsTable;

	rotatedCoorsTable.init(	coors,	//Real *coors,
				Nsites,	//Integer Nsites,
				Nrotations	//Integer Nrotations
				);
	
	printf("finding the best rotations...\n");

	Integer S=0;
	Integer *pProbable = probableGmax;
	for(i=0;i<N;i++, pProbable++) S+=*pProbable;
		


	Real *Gmax = (Real *)malloc( N * sizeof(Real));
	Real *PsiMax =  (Real *)malloc( N * sizeof(Real));
	Real *ThetaMax =  (Real *)malloc( N * sizeof(Real));
	Real *PhiMax =  (Real *)malloc( N * sizeof(Real));

	setArrayScalar<Real,Real>(	Gmax,	//DataType *dst,
					0,	//ScalarType scalar,
					N	//Integer N
				);

	Real dAng = 2*M_PI/Nrotations;
//	Real *rotatedCoors = (Real *)malloc( Nsites * 3 * sizeof(Real) );
  	
//	Real Rot[9];	


	Real x0,y0,z0;
	Real *pGmax = Gmax;
	Real *pPsiMax = PsiMax;
	Real *pPhiMax = PhiMax;
	Real *pThetaMax = ThetaMax;
	pProbable = probableGmax;
	Integer count=0;
	Integer tik = S/100;
	Real G;
	GAMMA_FOR(&grid)
	{

		if(*pProbable)
		{

		count++;
		if( count % tik == 0)
			printf("%3.0lf%%  [ %8ld /%8ld ] \n",(double)count/S*100,count,S);

		x0 = GAMMA_FOR_X;
		y0 = GAMMA_FOR_Y;
		z0 = GAMMA_FOR_Z;

		*pGmax = 0;

		RotatedCoorsIterator it(&rotatedCoorsTable);

		while(!it.isOver())
		{

			Real *rotatedCoors = it.getData();

			G =  calculateLocalG( 	
					g_index,	//Real **g_index, // array of g functions in real (see N )	
					&grid,	//Grid3DRISM * grid, 	
					rotatedCoors,	//Real *coors,	// coordinates of the solvent molecule 
					Nsites,	//int Nsites, // number of atoms in solvent (NO Multiple nsites!! all multiplicities=1, (eg for water N=3))
					x0,	//Real x0,
					y0,	//Real y0,
					z0	//Real z0
					);

			if(G>*pGmax)
			{
				*pGmax = G;
				*pPhiMax = it.getPhi();
				*pPsiMax = it.getPsi();
				*pThetaMax = it.getTheta();
			}


			it.next();
		}//while


		}//if pProbable

		pGmax++;
		pPhiMax++;
		pThetaMax++;
		pPsiMax++;
		pProbable++;
	
	}
	END_GAMMA_FOR

	printf("building refined table of rotations...\n");

	RotatedCoorsTable fineRotatedCoorsTable;

	fineRotatedCoorsTable.init(	
				coors,	//Real *coors,
				Nsites,	//Integer Nsites,
				Nrotations * Nrefinments	//Integer Nrotations
				);


	printf("refining the angle distributions...\n");

//	 dAng = 2*M_PI/Nrotations/Nrefinments;
//	Real *rotatedCoors = (Real *)malloc( Nsites * 3 * sizeof(Real) );
  	
//	Real Rot[9];	

	pGmax = Gmax;
	pPsiMax = PsiMax;
	pPhiMax = PhiMax;
	pThetaMax = ThetaMax;
	pProbable = probableGmax;
	count=0;
	tik = S/100;

	GAMMA_FOR(&grid)
	{

		if(*pProbable)
		{

		count++;
		if( count % tik == 0)
			printf("%3.0lf%%  [ %8ld /%8ld ] \n",(double)count/S*100,count,S);

		if(*pGmax >= treshold )
		{

		x0 = GAMMA_FOR_X;
		y0 = GAMMA_FOR_Y;
		z0 = GAMMA_FOR_Z;

		*pGmax = 0;

		//RotatedCoorsIterator it(&rotatedCoorsTable);

		Real phi0 = *pPhiMax;
		Real psi0 = *pPsiMax;
		Real theta0 = *pThetaMax;

//		while(!it.isOver())

//		{
		Integer NrotationsNew = Nrotations * Nrefinments;
		Real ddAng = 2*M_PI/NrotationsNew;

		Real phi,psi,theta;
		Integer phiId,psiId,thetaId;
		for(phi = phi0 - dAng; phi < phi0 + dAng; phi+=ddAng)
		{
			if(phi>=0)	
				phiId = phi/ddAng;
			else 	
				phiId = (phi+2*M_PI)/ddAng;
			
	
		for(theta = theta0 - dAng; theta < theta0 + dAng; theta+=ddAng)	
		{

			if(theta>=0)	
				thetaId = theta/ddAng;
			else 	
				thetaId = (theta+2*M_PI)/ddAng;
		for(psi = psi0 - dAng; psi < psi0 + dAng; psi+=ddAng)
		{
			if(psi>=0)	
				psiId = psi/ddAng;
			else 	
				psiId = (psi+2*M_PI)/ddAng;
	

//			printf("%lf %lf %lf\n ",phi,theta,psi);

			Real *rotatedCoors = 
				fineRotatedCoorsTable.getCoors(
					phiId,	//int phiId, 
					thetaId,	//int thetaId,
					psiId	// int psiId 
					);
;

			G =  calculateLocalG( 	
					g_index,	//Real **g_index, // array of g functions in real (see N )	
					&grid,	//Grid3DRISM * grid, 	
					rotatedCoors,	//Real *coors,	// coordinates of the solvent molecule 
					Nsites,	//int Nsites, // number of atoms in solvent (NO Multiple nsites!! all multiplicities=1, (eg for water N=3))
					x0,	//Real x0,
					y0,	//Real y0,
					z0	//Real z0
					);

			if(G>*pGmax)
			{
				*pGmax = G;
				*pPhiMax = phi;
				*pPsiMax = psi;
				*pThetaMax = theta;
			}

		}// psi
		}// theta
		}// phi
		
		}//if treshold
		}//if pProbable

		pGmax++;
		pPhiMax++;
		pThetaMax++;
		pPsiMax++;
		pProbable++;
	
	}
	END_GAMMA_FOR




	printf("writing output to files...\n");
	char fname[256];
	sprintf(fname,"%s_Gmax.3d",outputPrefix);
	printf("...%s\n",fname);	

	writeDoubleArrayToFile(	fname,	//const char *fname,
				Gmax,	//Real *x,
				N	//Integer N
				);

	sprintf(fname,"%s_PhiMax.3d",outputPrefix);
	printf("...%s\n",fname);	

	writeDoubleArrayToFile(	fname,	//const char *fname,
				PhiMax,	//Real *x,
				N	//Integer N
				);

	sprintf(fname,"%s_PsiMax.3d",outputPrefix);
	printf("...%s\n",fname);	

	writeDoubleArrayToFile(	fname,	//const char *fname,
				PsiMax,	//Real *x,
				N	//Integer N
				);

	sprintf(fname,"%s_ThetaMax.3d",outputPrefix);
	printf("...%s\n",fname);	

	writeDoubleArrayToFile(	fname,	//const char *fname,
				ThetaMax,	//Real *x,
				N	//Integer N
				);



	free(probableGmax);
	free(g_index);
	free(g_data);
	g_index=NULL;
	g_data=NULL;
	
	free(Gmax);
	free(PhiMax);
	free(PsiMax);
	free(ThetaMax);
	free(coors);		

} catch(Exception *e) {
	printf("Exception: %s\n",e->toString());

} catch(const char *str) {
	printf("Exception: %s\n",str);
}

return 0;
}
