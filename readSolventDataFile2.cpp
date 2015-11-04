#include "readSolventDataFile2.h"

#include <stdlib.h>
#include <string.h>

#include "Units.h"


#include "MoleculeLJParameters.h"
#include "MoleculeCharges.h"
#include "SiteMultiplicities.h"
#include "SiteDensities.h"

#include "readDoubleTable.h"
#include "getColumns.h"

void readSolventDataFile2(
		const char *fname,
		const char *distanceUnits,
		const char *energyUnits,
		const char *densityDistanceUnits,
		MoleculeLJParameters *LJ,//output argument
		MoleculeCharges *charges,//output argument
		SiteMultiplicities *siteMultiplicities, // output argument
		SiteDensities *siteDensities
	)
{
	Real *data;
	Integer nlin,ncol;

	readDoubleTable(fname,		//const char *fname,
			&nlin,		//Integer *nlin,	//out
			&ncol,		//Integer *ncol,	//out
			&data		//Real **result //out, will be allocated
			);

	Integer i;
	Real *cdata = (Real *)malloc(nlin*ncol*sizeof(Real));
	Real **cols = (Real **)malloc(ncol*sizeof(Real *));

	getColumns(	data,	//Real *matrix, 
			nlin,	//Integer nlin,
			ncol,	//Integer ncol,
			cdata,	//Real *columnData, // out
			cols	//		Real **columns    // out
		);

	free(data);


	LJ->allocData(nlin);
	charges->allocData(nlin);
	siteMultiplicities->allocData(nlin);
	siteDensities->allocData(nlin);

	memcpy(LJ->getSigma(),cols[0],nlin*sizeof(Real));
	memcpy(LJ->getEpsilon(),cols[1],nlin*sizeof(Real));
	memcpy(charges->getCharge(),cols[2],nlin*sizeof(Real));
	memcpy(siteMultiplicities->getDoubleData(),cols[3],nlin*sizeof(Real));
	memcpy(siteDensities->getDensity(),cols[4],nlin*sizeof(Real));
	
	Real kDistance = Units::distanceUnits()->unit2unit(distanceUnits,"Bohr");
	Real kEnergy = Units::energyUnits()->unit2unit(energyUnits,"Hartree");

	Real kDensity = 1/Units::distanceUnits()->unit2unit(densityDistanceUnits,"Bohr");

	kDensity = kDensity*kDensity*kDensity;

	Real *sigma=LJ->getSigma();
	Real *epsilon = LJ->getEpsilon();
	Real *density = siteDensities->getDensity();

	for(i=0;i<nlin;i++,sigma++,epsilon++,density++)
	{
		*sigma 	*= kDistance;
		*epsilon *= kEnergy;
		*density *= kDensity;
	}

	siteMultiplicities->convertData();

	free(cdata);
	free(cols);
}
