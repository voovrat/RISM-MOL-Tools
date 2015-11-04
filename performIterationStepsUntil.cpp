#include "performIterationStepsUntil.h"
#include "Condition.h"
#include "Solution.h"
#include "IterationStep.h"
#include "IterationDivergeException.h"


void performIterationStepsUntil(Condition *condition,
				IterationStep *iterationStep,
			    	Solution *initialGuess, 
			    	Solution *gridDifference,
			 	Solution *result,
				SolutionFactory *factory)
{

	Solution *x,*y,*src,*dst,*tmp;
	Integer condition_check;

	x=factory->createSolution(initialGuess->getGrid());
	y=result; //initialGuess->factory(m_grids[level]);

	src=x;
	dst=y;	

	initialGuess->copy(src);

	do
	{
		iterationStep->doIterationStep(src,gridDifference,dst);
		tmp = src; src=dst; dst=tmp;


	condition_check = 0;
		try{
			condition_check = condition->check(src,dst);
		} 
		catch ( IterationDivergeException *ex)
		{
			iterationStep->onIterationDiverge(ex);	
		}
	
	}while(!condition_check);

	if(src==result) NULL_DELETE(dst)
	else
	{  src->copy(result);
	   NULL_DELETE(src)
	}
}
