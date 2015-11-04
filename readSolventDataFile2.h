#ifndef readSolventDataFile2_h
#define readSolventDataFile2_h

class MoleculeLJParameters;
class MoleculeCharges;
class SiteMultiplicities;
class SiteDensities;

void readSolventDataFile2(
		const char *fname,
		const char *distanceUnits,
		const char *energyUnits,
		const char *densityDistanceUnits,
		MoleculeLJParameters *LJ,//output argument
		MoleculeCharges *charges,//output argument
		SiteMultiplicities *siteMultiplicities, // output argument
		SiteDensities *siteDensities	//output argument
	);

#endif
