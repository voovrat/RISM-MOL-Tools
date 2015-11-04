#ifndef SequentialNormCondition_h
#define SequentialNormCondition_h

#include "NormCondition.h"

class Solution;
class Norm;

class SequentialNormCondition : public NormCondition
{
protected:
//	Real (*m_norm)(Solution*,Solution*); inherited
//	Real m_tolerance;
	Real m_error;

public:
	SequentialNormCondition(	Norm *norm,
				Real tolerance)
	: NormCondition(norm,tolerance)
	{	
		//m_norm = norm;  inherited
		//m_tolerance = tolerance;
		m_error=0;
	}

//inherited
//	virtual void setTolerance(Real tolerance)
//	{
//		m_tolerance = tolerance;
//	}

// inherited
//	virtual Real getTolerance()
//	{
//		return m_tolerance;
//	}

	virtual Real getPrevError()
	{
		return m_error;
	}

	virtual Integer check(Object* a,Object *b);

};


class SequentialNormConditionFactory : public NormConditionFactory 
{
protected:
	Real m_tolerance;

	virtual NormCondition *newNormCondition(Norm *norm)
	{
		return new SequentialNormCondition(norm,m_tolerance);
	}
public:
	SequentialNormConditionFactory(GridDependentNormFactory *normFactory,
				Real tolerance)
	: NormConditionFactory(normFactory)
	{ m_tolerance = tolerance;}
};



#endif
