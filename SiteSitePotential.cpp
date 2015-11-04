#include "SiteSitePotential.h"

#include <stdio.h>

#include "Exception.h"

void SiteSitePotential::saveToFile( 	const char *fname,
				Real dr,
				Real Rmax)
{
FILE *f = fopen(fname,"w");

if(!f)
	throw new Exception(this,"SiteSitePotential::saveToFile: cannot open output file");

Real r;
Integer soluteSite,solventSite;
for(r=dr;r<Rmax;r+=dr)
{
	fprintf(f,"%lf\t",r);
	for(soluteSite = 0; soluteSite<getNumSoluteSites(); soluteSite++)
	{
		for(solventSite = 0; solventSite < getNumSolventSites(); solventSite++)
		{
			fprintf(f,"%lf\t",calculatePotential(soluteSite,solventSite,r));
		}

	}
	fprintf(f,"\n");
}


fclose(f);

}

