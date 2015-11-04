#include "MDIISIterationStep.h"

#include "Solution.h"
#include "Operator.h"

void MDIISIterationStep::solve()
{
	DIISIterationStep::solve();
	
	if(m_skipMatrixShift) 
	{	reset();
		m_skipMatrixShift=0;
	}

}

// x' = (1 - preDamping) * x[n] +  preDamping * sum(alpha[i]*x[i])
// x[n+1] = (1 - postDamping) * x' + postDamping * F[x']
void MDIISIterationStep::constructResult(Solution *result,Solution *gridDifference)
{
	DIISIterationStep::constructResult(result,gridDifference);
	
	Solution *tmp = m_solutionFactory->createSolution(result->getGrid());
  
	m_solutionVector->getAt(m_n-1,0)->copy(tmp); // tmp = x[n]
	m_mulScalar(tmp,1-m_preDamping);	// tmp = (1-preDumping) * x[n]
	
	m_mulScalar(result,m_preDamping);	// result = preDamping * sum(alpha[i]*x[i])
        m_add(result,tmp);			// result = (1 - preDamping) * x[n] +  preDamping * sum(alpha[i]*x[i])
 
	

	m_oper->F(result,tmp);   // tmp = F[x] 
	m_add(tmp,gridDifference); // tmp = F[x] +GD

	


	m_mulScalar(result,1-m_postDamping); // result = (1-mu)*x
	m_mulScalar(tmp,m_postDamping); // tmp = mu * (Fx + GD)

	m_add(result,tmp); // result = (1-mu)*x + mu * (Fx + GD)

	NULL_DELETE(tmp);

}



