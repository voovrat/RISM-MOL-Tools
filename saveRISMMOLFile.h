#ifndef saveRISMMOLFile_h
#define saveRISMMOLFile_h

void saveRISMMOLFile(
		const char *fname,
		const char *distanceUnits,
		const char *energyUnits,
		MoleculeCoordinates *coors, //output argument
		MoleculeLJParameters *LJ,//output argument
		MoleculeCharges *charges//output argument
	);


#endif
