#include "readRISMMOLFile.h"
#include <stdlib.h>

#include "Units.h"
#include "sizeOfFile.h"
#include "StringParser.h"

#include "countLines.h"
#include "MoleculeData.h"

#include "checkParseError.h"

#include "MoleculeCoordinates.h"
#include "MoleculeLJParameters.h"
#include "MoleculeCharges.h"

#include "Exception.h"

void readRISMMOLFile(
		const char *fname,
		const char *distanceUnits,
		const char *energyUnits,
		MoleculeCoordinates *coors, //output argument
		MoleculeLJParameters *LJ,//output argument
		MoleculeCharges *charges//output argument
	)
{
	Integer N = sizeOfFile(fname);

	if(N==0)
	{
		char Error[256];
		sprintf(Error,"readRISMMOLFile : cannot open %s\n",Error);
		throw new Exception(NULL,Error);
	}

	char *S=(char *)malloc(N+1);

	FILE *f = fopen(fname,"rb");
	fread(S,1,N,f);
	S[N]=0;
	fclose(f);

	Integer Nlin = countLines(S);
	coors->allocData(Nlin);
	LJ->allocData(Nlin);
	charges->allocData(Nlin);

	StringParser sp(S);

	Real kDistance = Units::distanceUnits()->unit2unit(distanceUnits,"Bohr");
	Real kEnergy = Units::energyUnits()->unit2unit(energyUnits,"Hartree");

	Real *X = coors->getX();
	Real *Y = coors->getY();
	Real *Z = coors->getZ();
	Real *sigma = LJ->getSigma();
	Real *epsilon = LJ->getEpsilon();
	Real *charge = charges->getCharge();


#ifdef PARSE_VAL
#error FF
#endif

#define PARSE_VAL(name,koef)			\
	sp.skipSpace();				\
	name[lin]=sp.getDouble() * koef;	\
	checkParseError(&sp,S);	


	Integer lin;
	for(lin=0; !sp.isOver(); lin++)
	{

		PARSE_VAL(X,kDistance)
		PARSE_VAL(Y,kDistance)
		PARSE_VAL(Z,kDistance)
		PARSE_VAL(sigma,kDistance)
		PARSE_VAL(epsilon,kEnergy)
		PARSE_VAL(charge,1)

		sp.skipSpace();
		if(!sp.isOver()) sp.skipEOL();
		checkParseError(&sp,S);

#undef PARSE_VAL

	}

	free(S);
}
