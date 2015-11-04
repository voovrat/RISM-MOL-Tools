#ifndef SiteSitePotential_h
#define SiteSitePotential_h

#include "Object.h"

class SiteSitePotential : public Object
{
public:

	virtual Real calculatePotential(Integer soluteSite,Integer solventSite,Real R)=0;

	virtual Integer getNumSoluteSites() = 0;
	virtual Integer getNumSolventSites() = 0;

	virtual void saveToFile( 	const char *fname,
					Real dr,
					Real Rmax);
};


#endif
