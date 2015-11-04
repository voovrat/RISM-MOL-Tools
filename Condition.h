#ifndef Condition_h
#define Condition_h

#include "Object.h"

class GridDependentData;

class Condition : public Object
{
public:
	virtual Integer check(Object *,Object *)=0;

	virtual void restart() {}
};


class ConditionFactory : public Object
{
public:
	virtual Condition *createCondition(GridDependentData *)=0;
};

#endif
