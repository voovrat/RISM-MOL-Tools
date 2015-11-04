#include "StatisticsBlackBoxSolverWrapper.h"
#include "Statistics.h"

void StatisticsBlackBoxSolverWrapper::solve(Solution *initialGuess,Solution *result)
{
	Statistics::getInstance()->startIteration();
	m_blackBoxSolver->solve(initialGuess,result);
	Statistics::getInstance()->endIteration();
}
