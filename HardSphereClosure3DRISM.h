#ifndef HardSphereClosure3DRISM_h
#define HardSphereClosure3DRISM_h

#include "Closure3DRISM.h"

class MoleculeCoordinates;
class Solution3DRISMR;
class GridIndependentInterface3DRISM;

class HardSphereClosure3DRISM : public Closure3DRISM
{
	Real *m_radii;
	Closure3DRISM *m_subClosure;
	MoleculeCoordinates *m_soluteCoordinates;
	
public:
	HardSphereClosure3DRISM( Real *radii ,
				 Closure3DRISM *subClosure,
				 MoleculeCoordinates *soluteCoordinates );

	virtual ~HardSphereClosure3DRISM() {}

	virtual void calculateClosure(	Solution3DRISMR *gamma,
					Solution3DRISMR *c //out
					);

};

class HardSphereClosureFactory3DRISM : public ClosureFactory3DRISM
{
protected:
	Real *m_radii;
	ClosureFactory3DRISM *m_subClosureFactory;
	GridIndependentInterface3DRISM *m_gridIndependent;

public:
	HardSphereClosureFactory3DRISM(	const char *radiiFile,
					const char *distanceUnits,
					ClosureFactory3DRISM *subClosureFactory,
					GridIndependentInterface3DRISM *gridIndependent
					);

	virtual ~HardSphereClosureFactory3DRISM();
	

	virtual Closure3DRISM *createClosure3DRISM(Solution3DRISMR *betaUshort);
};

#endif
