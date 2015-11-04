#ifndef AdaptiveDecayNormCondition_h
#define AdaptiveDecayNormCondition_h

#include "DecayNormCondition.h"

class AdaptiveDecayNormCondition : public DecayNormCondition
{
protected:

	Real m_decayFactorMultiplier;
	Real m_decayFactorDivider;
	Real m_minDecayFactor;	
	Real m_maxDecayFactor;
	Integer 	m_isDiverged;

public:


	AdaptiveDecayNormCondition(	
				Norm *norm,
				SolutionFactory *solutionFactory,
				Real initialDecayFactor  = 10,
				Real decayFactorMultiplier = 1.2,
				Real decayFactorDivider = 2,
				Real growFactor =2,
				Integer maxCount = 1000,
				Real minError = 1e-13,
				Real minDecayFactor = 1.1,
				Real maxDecayFactor = 100,
				Real firstGrowFactor=1
	)
	: DecayNormCondition(	initialDecayFactor, 	//Real decayFactor,
				norm,			//Norm *norm,
				solutionFactory,	//SolutionFactory *solutionFactory,
				growFactor,		//Real growFactor =2,
				maxCount,		//Integer maxCount = 1000,
				minError,		//Real minError = 1e-13
				firstGrowFactor
	)
	{
		m_decayFactorMultiplier = decayFactorMultiplier;
		m_decayFactorDivider = decayFactorDivider;
		m_prevError = 0;
		m_isDiverged = 0;
		m_minDecayFactor = minDecayFactor;
		m_maxDecayFactor = maxDecayFactor;
	}


	virtual Integer stateInit(Solution *x,Solution *y,Real error)
	{
		if(!m_firstSolution && m_prevError>0 && !m_isDiverged)
		{
			Real decayFactor = 1/m_errorOfTolerance;			

			if(error>m_prevError) 
				decayFactor /= m_decayFactorDivider;
			else
				decayFactor *= m_decayFactorMultiplier;

			if(decayFactor < m_minDecayFactor)
				decayFactor = m_minDecayFactor;

			if(decayFactor > m_maxDecayFactor)
				decayFactor = m_maxDecayFactor;

#ifdef PRINT_DECAY_FACTOR
			mexPrintf("decayFactor = %f\n",decayFactor);
#endif
			m_errorOfTolerance = 1/decayFactor;
		}

		m_isDiverged = 0;

		return DecayNormCondition::stateInit(x,y,error);
	}


		virtual Integer checkRealError(Solution *x,Solution *y,Real error)
		{
			return 1;
			//return !m_isDiverged;	// when diverge, can escape iterations only exceedig maxStepLimit
		}

	virtual Integer stateDiverge(Solution *x,Solution *y,Real error)
	{
		m_isDiverged = 1;
		return DecayNormCondition::stateDiverge(x,y,error);
	}

};

class AdaptiveDecayNormConditionFactory : public NormConditionFactory
{
protected:
	SolutionFactory *m_solutionFactory;
	Real m_initialDecayFactor;
	Real m_decayFactorDivider;
	Real m_decayFactorMultiplier;
	Real m_growFactor;
	Integer m_maxCount;
	Real m_minDecayFactor;
	Real m_maxDecayFactor;
	Real m_minError;
	Real m_firstGrowFactor;

	NormCondition *newNormCondition(Norm *norm)
	{
		return new AdaptiveDecayNormCondition(	
			norm,	//Norm *norm,
			m_solutionFactory, //SolutionFactory *solutionFactory,
			m_initialDecayFactor,//Real initialDecayFactor  = 10,
			m_decayFactorMultiplier,//Real decayFactorMultiplier = 1.2,
			m_decayFactorDivider,//Real decayFactorDivider = 2,
			m_growFactor,//Real growFactor =2,
			m_maxCount,//	Integer maxCount = 1000,
			m_minError,//	Real minError = 1e-13,
			m_minDecayFactor,//	Real minDecayFactor = 1.1,
			m_maxDecayFactor,//	Real maxDecayFactor = 100
			m_firstGrowFactor
		);

	}
public:
	AdaptiveDecayNormConditionFactory(
				GridDependentNormFactory *normFactory,
				SolutionFactory *solutionFactory,
				Real initialDecayFactor  = 10,
				Real decayFactorMultiplier = 1.2,
				Real decayFactorDivider = 2,
				Real growFactor =2,
				Integer maxCount = 1000,
				Real minError = 1e-13,
				Real minDecayFactor = 1.1,
				Real maxDecayFactor = 100,
				Real firstGrowFactor =1	
			)
	: NormConditionFactory(normFactory)
	{
		m_firstGrowFactor = firstGrowFactor;
		m_solutionFactory = solutionFactory;
		m_initialDecayFactor = initialDecayFactor;
		m_decayFactorMultiplier = decayFactorMultiplier;
		m_decayFactorDivider = decayFactorDivider;
		m_growFactor = growFactor;
		m_maxCount =  maxCount;
		m_minError = minError;
		m_minDecayFactor = minDecayFactor;
		m_maxDecayFactor = maxDecayFactor;
	}

};

#endif
