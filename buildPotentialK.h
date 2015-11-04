#ifndef buildPotentialK_h
#define buildPotentialK_h

class MoleculeCoordinates;
class SiteSitePotential;
class Solution3DRISMK;

void buildPotentialK (
	MoleculeCoordinates *soluteCoors,
	SiteSitePotential *siteSitePotentialK,
	Solution3DRISMK *potential3D // output
);


#endif
