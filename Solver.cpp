#include "Solver.h"
#include "Solution.h"

void Solver::solve(Solution *guess,Solution *result)
{
 	Solution *zero = m_solutionFactory->createSolution(guess->getGrid());
	zero->setZero();
	this->solve(guess,zero,result);
	NULL_DELETE(zero);
}
