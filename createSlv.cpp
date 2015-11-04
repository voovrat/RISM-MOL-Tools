#include "Exception.h"
#include "Settings.h"
#include "SolventComposition.h"
#include "JoinAndDistanceMatrices.h"
#include <stdio.h>
#include <stdlib.h>
#include "getMultiplicities.h"
#include "readDoubleTableSimple.h"

main(int argc,char *argv[])
{
try{


if(argc<3)
{
	puts("Usage: createSlv  solvent.composition solvent.rism [ output.slv ]");
	return 1;
}

FILE *fout;

if(argc>3)
{
	fout = fopen(argv[3],"w");
}
else 
	fout = stdout;


SolventComposition solventComposition;
solventComposition.init(argv[1]);

JoinAndDistanceMatrices matrices;
matrices.init(&solventComposition);

Integer N = matrices.getN();
Integer *mult = (Integer *)malloc(N * sizeof(Integer) );

getMultiplicities(	matrices.getJoins(),	//Integer *Joins,
			N,		//Integer N,
			mult	//Integer *multiplicities
		);

Integer nlin,ncol;
Real *rismInput;

readDoubleTableSimple(	argv[2],	//const char *fname,
			&nlin,	//Integer *nlin,	//out
			&ncol,	//Integer *ncol,	//out
			&rismInput	//Real **result //out, will be allocated
			);

if(ncol!=6) throw "Number of columns in RISM input file is incorrect";
if(nlin!=N) throw "Rism input file is inconsistent with the solvent composition file";

Real *pDens = solventComposition.getBigDensities();
Integer *pRdfNum = matrices.getRdfNums();
Real *pRism = rismInput;
Integer *pMult = mult;
int i;

for(i=0;i<N;i++, pRdfNum++, pDens++, pMult++, pRism+=6)
{
	if(*pRdfNum == -1) continue;
	fprintf(fout,"%lg\t%lg\t%lg\t%ld\t%lg\n",pRism[3],pRism[4],pRism[5],*pMult,*pDens);
}

free(mult);
free(rismInput);

} catch (Exception *e) {
	puts(e->toString());
} catch (const char *str) {

	puts(str);
}

return 0;
}
