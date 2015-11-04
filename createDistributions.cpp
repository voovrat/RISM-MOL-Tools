#include "Exception.h"
#include "Settings.h"
#include "SolventComposition.h"
#include "JoinAndDistanceMatrices.h"
#include <stdio.h>
#include <stdlib.h>
//#include "getMultiplicities.h"
#include <string.h>

main(int argc,char *argv[])
{
try{


if(argc<3)
{
	puts("Usage: createDistributuions prefix  solvent.composition ");
	puts("the files with names prefix_componend.distr will be created...");
	return 1;
}

const char *prefix  = argv[1];
const char *solventCompositionFile = argv[2];


SolventComposition solventComposition;
solventComposition.init(solventCompositionFile);

JoinAndDistanceMatrices matrices;
matrices.init(&solventComposition);

Integer N = matrices.getN();
//Integer *mult = (Integer *)malloc(N * sizeof(Integer) );

//getMultiplicities(	matrices.getJoins(),	//Integer *Joins,
//			N,		//Integer N,
//			mult	//Integer *multiplicities
//		);


Integer *pRdfNum = matrices.getRdfNums();
//Integer *pMult = mult;
int i;
Integer rdfNum = 0;

std::list<std::list<AtomRecord> *>::iterator it;
std::list<std::string>::iterator itStr;
for(	it=solventComposition.getAtomListList()->begin(),
	itStr = solventComposition.m_structureFiles.begin();
    	it!=solventComposition.getAtomListList()->end();
	it++,itStr++)
{
	std::list<AtomRecord> *atomlist = *it;
	Integer N = atomlist->size();

	char solventFile[256];
	char fname[256];
	strcpy(solventFile,(*itStr).c_str());
	char *p = strchr(solventFile,'.');
	if(p) *p=0;
	
	sprintf(fname,"%s_%s.distr",prefix,solventFile);
	FILE *f = fopen(fname,"w");
	
	
	for(i=0;i<N;i++,pRdfNum++)
	{
		if(*pRdfNum>=0) rdfNum = *pRdfNum;
		fprintf(f,"%s_g%ld.3d\n",prefix,rdfNum);
	}
	fclose(f);

}


//free(mult);

} catch (Exception *e) {
	puts(e->toString());
} catch (const char *str) {

	puts(str);
}

return 0;
}
