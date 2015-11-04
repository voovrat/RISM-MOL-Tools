#include <stdio.h>

#include "MoleculeCoordinates.h"
#include "MoleculeLJParameters.h"
#include "MoleculeCharges.h"

#include "readRISMMOLFile.h"
#include "saveRISMMOLFile.h"
#include "Exception.h"

#include <string.h>
#include <stdlib.h>

#define INF 1e9

main(Integer argc,char *argv[])
{


try{
char inputFile[256];
char outputFile[256];

const char *distanceUnits = "Bohr";
const char *energyUnits = "Hartree";

if(argc<=2)
{
	puts("./centrateSolute input.rism  output.rism ");
	return 1;
}


strcpy(inputFile,argv[1]);
strcpy(outputFile,argv[2]);

	MoleculeCoordinates coors;	
	MoleculeLJParameters LJ;
	MoleculeCharges charges;

	readRISMMOLFile(
			inputFile,	//const char *fname,
			distanceUnits,	//const char *distanceUnits,
			energyUnits,	//const char *energyUnits,
			&coors,		//MoleculeCoordinates *coors, //output argument
			&LJ,		//MoleculeLJParameters *LJ,//output argument
			&charges	//MoleculeCharges *charges//output argument
	);

	Integer Nsites = coors.getNumSites();
	Real minX = INF;
	Real maxX = -INF;

	Real minY = INF;
	Real maxY = -INF;

	Real minZ = INF;
	Real maxZ = -INF;

	Integer i;
	for(i=0;i<Nsites;i++)
	{
		if(coors.getX()[i]<minX) minX = coors.getX()[i];
		if(coors.getX()[i]>maxX) maxX = coors.getX()[i];

		if(coors.getY()[i]<minY) minY = coors.getY()[i];
		if(coors.getY()[i]>maxY) maxY = coors.getY()[i];

		if(coors.getZ()[i]<minZ) minZ = coors.getZ()[i];
		if(coors.getZ()[i]>maxZ) maxZ = coors.getZ()[i];
	}	

	Real meanX = (maxX + minX)/2;
	Real meanY = (maxY + minY)/2;
	Real meanZ = (maxZ + minZ)/2;


	for(i=0;i<Nsites;i++)
	{
		coors.getX()[i] -= meanX;
		coors.getY()[i] -= meanY;
		coors.getZ()[i] -= meanZ;

	
	}	
	saveRISMMOLFile(
		outputFile,	//const char *fname,
		distanceUnits,	//const char *distanceUnits,
		energyUnits,	//const char *energyUnits,
		&coors,		//MoleculeCoordinates *coors, //output argument
		&LJ,		//MoleculeLJParameters *LJ,//output argument
		&charges	//MoleculeCharges *charges//output argument
	);

return 0;

}catch(Exception *e)
{
printf("Exception : %s\n",e->toString());
delete e;
return 1;
}

}
