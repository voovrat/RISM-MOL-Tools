#ifndef AdjustableDampedIterationStep_h
#define AdjustableDampedIterationStep_h

#include "DampedIterationStep.h"
#include "TextLog.h"

class Solution;

class AdjustableDampedIterationStep :  public DampedIterationStep
{
protected:

// inherited:
	//Real m_lambda;
	//IterationStep *m_iterationStep;
	//void (*m_add)(Solution *,Solution *);
	//void (*m_sub)(Solution *,Solution *);
	//void (*m_mulScalar)(Solution *,Real);

	Real m_lambdaDecayFactor;
	Real m_minLambda;

public:
  
	AdjustableDampedIterationStep
		(	IterationStep *iterationStep,
			void (*add)(Solution *,Solution *),
			void (*sub)(Solution *,Solution *),
			void (*mulScalar)(Solution *,Real),
			DoubleParameter *initialLambda ,
			Real lambdaDecayFactor = 10 ,
			Real minLambda = 1e-3)
	: DampedIterationStep (
			iterationStep,
			add,
			sub,
			mulScalar,
			initialLambda
		)
	{
		m_lambdaDecayFactor = lambdaDecayFactor;
		m_minLambda = minLambda;
	}

//inherited:		
	//Real getLambda() {return m_lambda;}
	//Real setLambda(Real lambda) {m_lambda = lambda;}

//inherited:
   	//void doIterationStep(Solution *guess,Solution *gridDifference, Solution *result);

	virtual void onIterationDiverge(IterationDivergeException *ex)
	{
		if(getLambda()<m_minLambda)
			throw ex;
		else
			NULL_DELETE(ex);

		char s[256];
		sprintf(s,"Iteration Diverge:  LAMBDA reduced from %lg to %lg \n",getLambda(),getLambda()/m_lambdaDecayFactor);

		TextLog::getInstance()->printString(1,s);
		setLambda(getLambda()/m_lambdaDecayFactor);
	
	}
	
};

class AdjustableDampedIterationStepFactory : public DampedIterationStepFactory
{
protected:
//inherited
	//Real m_lambda;
	//IterationStepFactory *m_subFactory;
	//void (*m_add)(Solution *,Solution *);
	//void (*m_sub)(Solution *,Solution *);
	//void (*m_mulScalar)(Solution *,Real);

	Real m_lambdaDecayFactor;

public:

	AdjustableDampedIterationStepFactory
			(	IterationStepFactory *subFactory, 
				void (*add)(Solution *,Solution *),
				void (*sub)(Solution *,Solution *),
				void (*mulScalar)(Solution *,Real),
				DoubleParameter *lambda,
				Real lambdaDecayFactor = 2)
	: DampedIterationStepFactory(
				subFactory,
				add,
				sub,
				mulScalar,
				lambda)
	{
		m_lambdaDecayFactor =  lambdaDecayFactor;
	}

	IterationStep *createIterationStep(Operator *F)
	{
		IterationStep *subIterationStep = m_subFactory->createIterationStep(F);
		AdjustableDampedIterationStep *result = 
			new AdjustableDampedIterationStep(
				subIterationStep,
				m_add,
				m_sub,
				m_mulScalar,
				m_lambda,
				m_lambdaDecayFactor
			);

		result->addToDeleteList(subIterationStep);

		return result;
	}

};


#endif
