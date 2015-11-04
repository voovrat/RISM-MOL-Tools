#include "DampedIterationStep.h"


void DampedIterationStep::doIterationStep(
	Solution *guess,
	Solution *gridDifference,
	Solution *result)
{
	m_iterationStep->doIterationStep(guess,gridDifference,result); // r=Fx
	m_sub(result,guess); // r= Fx-x
	m_mulScalar(result,m_lambda->getDouble());	// r=L(Fx-x)
	m_add(result,guess);		// r=x+L(Fx-x)
}

