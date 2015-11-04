#include "HNCClosure3DRISM.h"

#include "calculateBeta.h"
#include "Solution3DRISMR.h"

HNCClosure3DRISM::HNCClosure3DRISM(
				Solution3DRISMR *betaUshort
				)
{
	m_betaUShort = betaUshort;
}

HNCClosure3DRISM::~HNCClosure3DRISM()
{
}

void HNCClosure3DRISM::calculateClosure(Solution3DRISMR *gamma,
					Solution3DRISMR *c //out
					)
{
	// c = exp(-beta UShort + gamma) - gamma -1
//	Solution3DRISMR *tmp = m_SolutionFactory->createSolution(gamma->getGrid());
	
	m_betaUShort->copy(c); 		// c = -beta*UShort
	addSolution3DRISMR(c,gamma);	// c = -beta*UShort + gamma
	expSolution3DRISMR(c);		// c = exp(-beta*UShort + gamma)
	subSolution3DRISMR(c,gamma);	// c = exp(-beta*UShort + gamma) - gamma
	subScalarSolution3DRISMR(c,1);	// c = exp(-beta*Ushort + gamma) - gamma - 1	

}

