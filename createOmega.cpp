#include "SolventComposition.h"
#include <stdio.h>
#include "writeOmega.h"
#include "JoinAndDistanceMatrices.h"

main(int argc,char *argv[])
{
try{

if(argc<2)
{
puts("Usage: ./createOmega solvent.composition  [output.omega]  ");
puts("Bu default: output to stdout");
return 1;
}

FILE *fout;

if(argc>2)
{
	fout = fopen(argv[2],"w");
}
else
	fout = stdout;

SolventComposition solventComposition;
solventComposition.init(argv[1]);
JoinAndDistanceMatrices matrices;

matrices.init(&solventComposition);

writeOmega(	matrices.getRdfNums(),	//Integer *RDFNum,
		matrices.getJoins(),	//Integer *Joins,
		matrices.getDistances(),//Real *distances,
		matrices.getN(),		//Integer BigN,
		fout		//FILE *f
		);

} catch (const char *str)
{
puts(str);
}

return 0;
}


