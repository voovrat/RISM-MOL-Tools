#include "saveRISMMOLFile.h"
#include "Units.h"

void saveRISMMOLFile(
		const char *fname,
		const char *distanceUnits,
		const char *energyUnits,
		MoleculeCoordinates *coors, //output argument
		MoleculeLJParameters *LJ,//output argument
		MoleculeCharges *charges//output argument
	)
{

FILE *f = fopen(fname,"w");


Integer Nsites = coors->getNumSites();
Integer i;

Real kDistance = Units::distanceUnits()->unit2unit("Bohr",distanceUnits);
Real kEnergy = Units::energyUnits()->unit2unit("Hartree",energyUnits);


for(i=0;i<Nsites;i++)
{
	fprintf(f,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",
		coors->getX()[i]*kDistance,
		coors->getY()[i]*kDistance,
		coors->getZ()[i]*kDistance,
		LJ->getSigma()[i]*kDistance,
		LJ->getEpsilon()[i]*kEnergy,
		charges->getCharge()[i]
	);

}

fclose(f);



}
