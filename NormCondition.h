#ifndef NormCondition_h
#define NormCondition_h

#include "Condition.h"
class Norm;
#include "GridDependentNormFactory.h"

class NormCondition : public Condition
{
protected:
	
	Norm *m_norm;
	Real m_tolerance;
public:
	NormCondition(	Norm *norm,
			Real tolerance)
	{	
		m_norm = norm;
		m_tolerance = tolerance;
	}

	virtual void setTolerance(Real tolerance)
	{
		m_tolerance = tolerance;
	}

	virtual Real getTolerance()
	{
		return m_tolerance;
	}

	virtual Real getPrevError() =0;

	virtual Integer check(Object* a,Object *b)=0;

};

class NormConditionFactory : public ConditionFactory
{
protected:
	GridDependentNormFactory *m_normFactory;

	virtual NormCondition *newNormCondition(Norm *norm)=0;

public:
	NormConditionFactory(	GridDependentNormFactory *normFactory )
	{
		m_normFactory = normFactory;
	}

	virtual Condition *createCondition(GridDependentData *gridDependent)
	{
		Norm *norm = m_normFactory->createNorm(gridDependent);
		Condition *condition = newNormCondition(norm);
		condition->addToDeleteList(norm);
		return condition;
	}
	

};

#endif
