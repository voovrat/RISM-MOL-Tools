#include "Settings.h"
#include <list>
#include "AtomRecord.h"
#include "ArrayOperations.h"
#include "MatrixOperation.h"
#include <stdlib.h>
#include "atomlist2coors.h"
#include "calculateDistances.h"

// put distances for different molecules in one matrix
// distances between the molecules are -1. 

void buildBigDistances(	std::list<std::list<AtomRecord> *> *atomListList,
			Integer BigN, // total number of sites in all molecules
			Real *BigDistances // out, pre-allocated BigN*BigN*sizeof(Real)
			)
{
Integer BigN2 = BigN * BigN;

setArrayScalar<Real,Real>(	BigDistances, 	//DataType *dst,
				-1,		//ScalarType scalar,
				BigN2		//Integer N
			);

Real *coors = (Real *)malloc( BigN * 3 * sizeof(Real) ); // allocate more than enough to avoid allocation in the cycle
Real *dist = (Real *)malloc( BigN2 * sizeof(Real) );

int currLine = 0;
std::list<std::list<AtomRecord> *>::iterator it;
for(it = atomListList->begin(); it!=atomListList->end(); it++)
{
	int N = (*it)->size();
	
	atomlist2coors(	*it,	//std::list<AtomRecord> *atomlist,
			coors	//Real *coors //Nsites * 3 real array
			);

	calculateDistances(	coors,	//Real *coors,
				N,	//Integer Nsites,
				dist	//,Real *distances,
				//Integer Dim =3
			);

	copyMatrix<Real>(	BigDistances + currLine*BigN + currLine,	//T *dst,	
				1,		//Integer dst_xstep,
				BigN,		//Integer dst_ystep,
				dist,		//T *src,			
				1,		//Integer src_xstep,
				N,		//Integer src_ystep,
				N,		//Integer xsize,		
				N		//Integer ysize
			);			

	currLine += N;
}

free(coors);
free(dist);

}
/*
#include "SolventComposition.h"
#include <stdio.h>
#include "joinDistances.h"
#include "removeJoined.h"
#include "numerateRDFs.h"

template<class T>
inline void printMatrix(T *matrix, int M,int N,const char *format)
{
int i,j;
T *p = matrix;
for(i=0;i<M;i++)
{
	for(j=0;j<N;j++,p++)
	{
		printf(format,*p); 
	}
	printf("\n");
}
}

main(int argc,char *argv[])
{
try{
SolventComposition solventComposition;

solventComposition.readComponentsFile(argv[1]);
solventComposition.readStructureFiles();
solventComposition.mergeStructureFiles();

printf("BigN:%ld\n",solventComposition.getBigN());

std::list<AtomRecord>::iterator it;
for(it=solventComposition.m_bigAtomList.begin(); 
    it!=solventComposition.m_bigAtomList.end();
    it++)
{
	AtomRecord atom = *it;
	printf("%s\t%lg\t%lg\t%lg\n",atom.element,atom.x,atom.y,atom.z);
}

Integer BigN = solventComposition.getBigN();
Integer BigN2 = BigN * BigN;

Real *BigDistances = (Real *)malloc( BigN2 * sizeof(Real) );

buildBigDistances(	&solventComposition.m_atomListList,	//std::list<std::list<AtomRecord> *> *atomListList,
			BigN,	//Integer BigN, // total number of sites in all molecules
			BigDistances	//Real *BigDistances // out, pre-allocated BigN*BigN*sizeof(Real)
			);

solventComposition.mergeStructureFiles();

Integer *Joins = (Integer *)malloc( BigN2 * sizeof(Integer));

joinDistances(	solventComposition.getBigAtomList(),	//std::list<AtomRecord> *atomlist,
		BigDistances,	//Real *distances,
		BigN,		//Integer Nsites,
		Joins		//Integer *Joins
		);

Integer *removedJoins = (Integer *)malloc( BigN2 * sizeof(Integer));


removeJoined(	Joins,	//Integer *Joins,
		BigN,	//Integer N,
		removedJoins	//Integer *RemovedJoins
		);

numerateRDFs(	removedJoins, BigN);

printMatrix<Real>(BigDistances,BigN,BigN,"%10lg");
printMatrix<Integer>(Joins,BigN,BigN,"%5ld");
puts("***");
printMatrix<Integer>(removedJoins,BigN,BigN,"%5ld");


free(removedJoins);
free(Joins);
free(BigDistances);

} catch (const char *str)
{
puts(str);
}

return 0;
}

*/
