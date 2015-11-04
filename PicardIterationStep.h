#ifndef PicardIterationStep_h
#define PicardIterationStep_h

#include "IterationStep.h"
//#include "Operator.h"

class Operator;


class PicardIterationStep :  public IterationStep
{
protected:
  
	Operator *m_F;
	void (*m_add)(Solution *,Solution *);



public:

	PicardIterationStep(	void (*add)(Solution *,Solution *),
				Operator *F)
	{
		m_add = add;
		m_F = F;
	}

	virtual ~PicardIterationStep() {}

	virtual void doIterationStep(	Solution *guess,
					Solution *gridDifference, 
					Solution *result);
};

class PicardIterationStepFactory : public IterationStepFactory 
{
protected:
	void (*m_add)(Solution *,Solution *);
public:
	PicardIterationStepFactory(void (*add)(Solution *,Solution *))
	{
		m_add = add;
	}

	IterationStep *createIterationStep(Operator *F)
	{
		return new PicardIterationStep(m_add,F);
	}
};

#endif
