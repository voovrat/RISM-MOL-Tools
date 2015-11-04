#ifndef buildPotential_h
#define buildPotential_h

class MoleculeCoordinates;
class SiteSitePotential;
class Solution3DRISMR;

void buildPotential (
	MoleculeCoordinates *soluteCoors,
	SiteSitePotential *siteSitePotential,
	Solution3DRISMR *potential3D // output
);

#endif
