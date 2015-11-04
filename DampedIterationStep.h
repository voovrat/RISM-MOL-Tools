#ifndef DumpedIterationStep_h
#define DumpedIterationStep_h

#include "IterationStep.h"
#include "DoubleParameter.h"

class Solution;

class DampedIterationStep :  public IterationStep
{
protected:

	DoubleParameter *m_lambda;
	IterationStep *m_iterationStep;
	void (*m_add)(Solution *,Solution *);
	void (*m_sub)(Solution *,Solution *);
	void (*m_mulScalar)(Solution *,Real);


public:
  
	DampedIterationStep(	IterationStep *iterationStep,
			void (*add)(Solution *,Solution *),
			void (*sub)(Solution *,Solution *),
			void (*mulScalar)(Solution *,Real),
			DoubleParameter *lambda )
	{
		m_iterationStep = iterationStep;
		m_add = add;
		m_sub = sub;
		m_mulScalar = mulScalar;
		m_lambda = (DoubleParameter *)lambda->clone();
	}
		
	virtual ~DampedIterationStep() 
	{
		NULL_DELETE(m_lambda);
	}
 
	Real getLambda() {return m_lambda->getDouble();}
	Real setLambda(Real lambda) {m_lambda->setDouble(lambda);}

   	void doIterationStep(Solution *guess,Solution *gridDifference, Solution *result);
};

class DampedIterationStepFactory : public IterationStepFactory
{
protected:
	DoubleParameter *m_lambda;
	IterationStepFactory *m_subFactory;
	void (*m_add)(Solution *,Solution *);
	void (*m_sub)(Solution *,Solution *);
	void (*m_mulScalar)(Solution *,Real);

public:

	DampedIterationStepFactory
			(	IterationStepFactory *subFactory, 
				void (*add)(Solution *,Solution *),
				void (*sub)(Solution *,Solution *),
				void (*mulScalar)(Solution *,Real),
				DoubleParameter *lambda)
	{
		m_subFactory = subFactory;
		m_add = add;
		m_sub = sub;
		m_mulScalar = mulScalar;
		m_lambda = (DoubleParameter *)lambda->clone();
	}

	virtual ~DampedIterationStepFactory()
	{
		NULL_DELETE(m_lambda);
	}

	IterationStep *createIterationStep(Operator *F)
	{
		IterationStep *subIterationStep = m_subFactory->createIterationStep(F);
		DampedIterationStep *result = 
			new DampedIterationStep(
				subIterationStep,m_add,m_sub,m_mulScalar,m_lambda
			);

		result->addToDeleteList(subIterationStep);

		return result;
	}

};


#endif
