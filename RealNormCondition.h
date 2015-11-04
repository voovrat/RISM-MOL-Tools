#ifndef RealNormCondition_h
#define RealNormCondition_h

#include "NormCondition.h"

class Solution;
class SolutionFactory;
				
class RealNormCondition : public NormCondition
{
protected:
	Solution *m_firstSolution;
	Real m_firstError;
	Real m_prevError;
	Integer m_state;

//	Real m_tolerance;
	Real m_errorOfTolerance; // in percents, how accurate should we estimate the tolerance
//	Real (*m_norm)(Solution *,Solution *);
	Norm *m_realNorm;
	SolutionFactory *m_solutionFactory;

	Integer m_n;		// number of iterations since restart
	Integer m_nGrowError;	// numer of iterations, when the error grows
	Integer m_maxCount;
	Real m_minError;
	Real m_firstGrowFactor;

	Real m_firstGrowError;
	Real m_prevGrowError;
	Real m_growFactor;	


	virtual Integer stateInit(Solution *x,Solution *y,Real error);

	virtual Integer stateCheck(Solution *x,Solution *y,Real error);
		virtual Integer checkRealError(Solution *x,Solution *y,Real error);

	virtual Integer stateDiverge(Solution *x,Solution *y,Real error);

	virtual void throwDivergeException();


public:

	RealNormCondition(	Real tolerance, 
				Real errorOfTolerance,
				Norm *fastNorm,
				Norm *realNorm,
				SolutionFactory *solutionFactory,				
				Real growFactor = 2,
				Integer maxCount = 1000,
				Real minError = 1e-13,
				Real firstGrowFactor = 1)
	: NormCondition(fastNorm,tolerance)
	{
//		m_tolerance = tolerance;
		m_errorOfTolerance = errorOfTolerance;
		m_realNorm = realNorm;
//		m_norm = fastNorm;
		m_growFactor = growFactor;
		m_firstSolution = NULL;
		m_solutionFactory = solutionFactory;
		m_minError = minError;
		m_maxCount = maxCount;
		m_firstGrowFactor = firstGrowFactor;

		restart();

	}

	virtual ~RealNormCondition();

	virtual void restart();

	virtual Integer getNIterations()
	{
		return m_n;
	}
	
	virtual Real getPrevError()
	{
		return m_prevError;
	}

	virtual Integer check(Object *,Object *);


};


class RealNormConditionFactory : public NormConditionFactory
{
protected:

		Real m_tolerance;	 
		Real m_decayFactor;
		GridDependentNormFactory *m_fastNormFactory;
		GridDependentNormFactory *m_realNormFactory;
		SolutionFactory *m_solutionFactory;
		Real m_growFactor;
		Integer m_maxCount;
		Real m_minError;
		Real m_firstGrowFactor;


	virtual NormCondition *newNormCondition(Norm *norm)
	{
		//is unused
		return NULL;
	}

public:
	RealNormConditionFactory(	Real tolerance,	 
					Real decayFactor,	
					GridDependentNormFactory *fastNormFactory,
					GridDependentNormFactory *realNormFactory,
					SolutionFactory *solutionFactory,				
					Real growFactor,
					Integer maxCount, 
					Real minError,
					Real firstGrowFactor =1 					
					)
	: NormConditionFactory(NULL)
	{
		m_tolerance = tolerance;	 
		m_decayFactor = decayFactor;
		m_fastNormFactory = fastNormFactory;
		m_realNormFactory = realNormFactory;
		m_solutionFactory = solutionFactory;
		m_growFactor = growFactor;
		m_maxCount = maxCount;
		m_minError = minError;		
		m_firstGrowFactor = firstGrowFactor;
	}

	virtual Condition *createCondition(GridDependentData *gridDependent)
	{
		Norm *realNorm = m_realNormFactory->createNorm(gridDependent);
		Norm *fastNorm = m_fastNormFactory->createNorm(gridDependent);

		NormCondition *normCondition =new RealNormCondition(	
					m_tolerance,	//Real tolerance, 
					1/m_decayFactor,	//Real errorOfTolerance,
					fastNorm,	//SequentialNormCondition,//Norm *fastNorm,
					realNorm,		//Norm *realNorm,
					m_solutionFactory,//SolutionFactory *solutionFactory,				
					m_growFactor,	//Real growFactor = 2,
					m_maxCount,	//Integer maxCount = 1000,
					m_minError,//Real minError = 1e-13
					m_firstGrowFactor
				);		
		normCondition->addToDeleteList(realNorm);
		normCondition->addToDeleteList(fastNorm);

		return normCondition;
	}
};

#endif
