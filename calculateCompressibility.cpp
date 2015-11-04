#include "TabFunction.h"

// Warning! Function work for one component solutions
// Result - in rdf units (Bohr^3) 
// Kaclulates kbT * kappa! 


// kappa = 1/denity + 4 pi int (g - 1)r^2 dr

Real calculateCompressibility(	TabFunction *rdf,
				Real density)
{

	Integer N = rdf->getTabSize();

	Real IntHsolv = 0;
	Real dr_solv = rdf->getTabStep();
	Real *solvPtr = rdf->getTab();
	Real r = dr_solv;
	while(N--)
	{
		IntHsolv += (*solvPtr - 1)*dr_solv*4*M_PI*r*r;
		solvPtr++;
		r+=dr_solv;
	}
	
	return 1/density + IntHsolv;



}
