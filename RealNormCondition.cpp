#include "RealNormCondition.h"
#include "Solution.h"
#include "Norm.h"
#include "IterationDivergeException.h"


void RealNormCondition::throwDivergeException()
{
	//restart();
	m_state=0;
	throw new IterationDivergeException(this,"RealNormCondition::stateDiverge : iteration diverge");
	
}


Integer RealNormCondition::stateInit(Solution *x,Solution *y,Real error)
{
	m_n=0;	
	m_nGrowError = 0;
			
	if(!m_firstSolution)
	{
		m_firstSolution = m_solutionFactory->createSolution(x->getGrid());
		m_prevGrowError = error * m_growFactor;
	}

	x->copy(m_firstSolution);
	m_firstError = error;
	m_state = 1;

	return 0;
}



Integer RealNormCondition::stateCheck(Solution *x,Solution *y,Real error)
{Integer result = 0;

	m_n++;

	if(error>m_prevError * m_firstGrowFactor ) 
	{	
#ifdef DEBUG_DIIS_DECAYFACTOR
	printf("stateCheck: %le>%le * %le (->stateDiverge)\n",error,m_prevError,m_firstGrowFactor);
#endif

		m_firstGrowError = error;
		result = stateDiverge(x,y,error);
		m_state = 2;
	}
		
	if(error < m_minError || m_n > m_maxCount) 
	{	

#ifdef DEBUG_DIIS_DECAYFACTOR
	printf("stateCheck: %le<%le || %ld>%ld\n",error,m_minError,m_n,m_maxCount);
#endif
	result =1; return 1;
	}

	if(error < m_errorOfTolerance * m_firstError)
	{

#ifdef DEBUG_DIIS_DECAYFACTOR
		printf("stateCheck: error =%le < %le * %le\n",error,m_errorOfTolerance,m_firstError);
#endif
		result = checkRealError(x,y,error);
		x->copy(m_firstSolution);
		m_firstError = error;
	}

	return result;
}

Integer RealNormCondition::checkRealError(Solution *x,Solution *y,Real error)
{
	Real realError = m_realNorm->calculateNorm(x,m_firstSolution);
	return realError<m_tolerance;
}
	

Integer RealNormCondition::stateDiverge(Solution *x,Solution *y,Real error)
{
	m_nGrowError++;
	if( m_nGrowError > m_maxCount/10) return 1; 

	if(error<m_firstGrowError / m_growFactor ) 
	{
		m_prevGrowError = m_firstGrowError;
		m_state=1;
	}
	else 
	if(   error > m_firstGrowError * m_growFactor
           || error > m_prevGrowError	// to prevent periodicity
	 )
		throwDivergeException();
	
	return 0;
}



Integer RealNormCondition::check(Object *X,Object *Y)
{
 	Solution *x = dynamic_cast<Solution *>(X);
	Solution *y = dynamic_cast<Solution *>(Y);

	Integer result;

	if(!x || !y ) 
		throw "RealNormCondition::check : input values should be of type Solution";

	Real error = m_norm->calculateNorm(x,y);
#if DEBUG_DIIS_DECAYFACTOR
	printf("\nRealNormCondition: check ::: Error=%le\n state = %ld",error,m_state);
#endif
	result = 0;

	switch(m_state)
	{
		case 0: result = stateInit(x,y,error);
			break;

		case 1: result = stateCheck(x,y,error);
			break;

		case 2: result = stateDiverge(x,y,error);
			break;
	};

	m_prevError = error;

	if(result) restart();

	return result;
}

void RealNormCondition::restart()
{
	if(m_firstSolution)
		NULL_DELETE(m_firstSolution);
	
	m_firstSolution = NULL;
	m_state = 0;
}

RealNormCondition::~RealNormCondition()
{
	if(m_firstSolution)
		NULL_DELETE(m_firstSolution);
	
	m_firstSolution = NULL;	
}
