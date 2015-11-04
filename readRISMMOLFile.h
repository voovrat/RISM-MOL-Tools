#ifndef readRISMMOLFile_h
#define readRISMMOLFile_h

class MoleculeCoordinates;
class MoleculeLJParameters;
class MoleculeCharges;


void readRISMMOLFile(
		const char *fname,
		const char *distanceUnits,
		const char *energyUnits,
		MoleculeCoordinates *coors, //output argument
		MoleculeLJParameters *LJ,//output argument
		MoleculeCharges *charge//output argument
	);


#endif
