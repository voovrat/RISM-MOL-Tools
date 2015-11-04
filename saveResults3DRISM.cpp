#include "saveResults3DRISM.h"

#include "Solution3DRISMR.h"
#include "saveGrid3DRISM.h"
#include "writeDoubleArrayToFile.h"
#include "HNCFreeEnergy3DRISM.h"

void saveResults3DRISM(	Solution3DRISMR *gamma,
			Solution3DRISMR *c,
			Solution3DRISMR *clong,
			Solution3DRISMR *g,
			Solution3DRISMR *minusBetaUshort,
			const char *prefix,
			const char *suffix
		)
{
	char tmpstr[256];

	Grid3DRISM *gg=(Grid3DRISM*)gamma->getGrid();

	saveGrid3DRISM(	gg,		//Grid3DRISM *,
			prefix,		//const char *fileNamePrefix,
			".grd"		//const char *fileNameSuffix
			);

	Integer numSites = gamma->getNumberOfSites();

	Integer site;
	Integer N = gamma->getSizeOfOneGamma();

	for(site=0;site<numSites;site++)
	{
		sprintf(tmpstr,"%sgamma%d%s",prefix,(int)site,suffix);
		writeDoubleArrayToFile(tmpstr,gamma->getGamma()[site],N);


		sprintf(tmpstr,"%sc%d%s",prefix,(int)site,suffix);
		writeDoubleArrayToFile(tmpstr,c->getGamma()[site],N);

		sprintf(tmpstr,"%sclong%d%s",prefix,(int)site,suffix);
		writeDoubleArrayToFile(tmpstr,clong->getGamma()[site],N);
	
	
		sprintf(tmpstr,"%sg%d%s",prefix,(int)site,suffix);
		writeDoubleArrayToFile(tmpstr,g->getGamma()[site],N);

		sprintf(tmpstr,"%sminusBetaUshort%d%s",prefix,(int)site,suffix);
		writeDoubleArrayToFile(tmpstr,minusBetaUshort->getGamma()[site],N);
	
	}//for site
	
}
