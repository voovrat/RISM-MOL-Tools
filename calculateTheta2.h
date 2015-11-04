#ifndef calculateTheta2_h
#define calculateTheta2_h

class MoleculeCoordinates;
class SiteMultiplicities;
class SiteSitePotential;
class Solution3DRISMK;

// \Theta_{\alpha} = \sum_{s=1}^{N_{solvent}} (-\beta \hat U^L) \chi_{s\alpha}

void calculateTheta2(	Real beta,
			MoleculeCoordinates *soluteCoors,
			SiteMultiplicities *siteMultiplicities,
			SiteSitePotential *longPotentialK,
			Solution3DRISMK ***chiIndex,
			Real **chiMultipliers,
			Solution3DRISMK *theta,			// out
			Solution3DRISMK *betaUlong=NULL		//-beta Ulong//out[optional]
		   );
	//if betaUlong=NULL it will not be returned
	

#endif
