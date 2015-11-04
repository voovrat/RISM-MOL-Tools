#include "SequentialNormCondition.h"
#include "Norm.h"

Integer SequentialNormCondition::check(Object* x,Object *y)
{
	Real diff = m_norm->calculateNorm(x,y);
	//mexPrintf("diff = %le\n",diff);
	return diff < m_tolerance;
}
	
