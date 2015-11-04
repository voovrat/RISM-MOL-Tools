#include "PicardIterationStep.h"
#include "Operator.h"
#include "Solution.h"

void PicardIterationStep::doIterationStep(Solution *guess,Solution *gridDifference, Solution *result)
{
	m_F->F(guess, result);
	m_add(result,gridDifference);	
}


