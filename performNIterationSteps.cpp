#include "performNIterationSteps.h"

#include "performIterationStepsUntil.h"
#include "CounterCondition.h"
#include "Solution.h"
#include "IterationStep.h"

//Performs N iteration steps
void performNIterationSteps(	Integer N,
			    	IterationStep *iterationStep,
			    	Solution *initialGuess, 
			    	Solution *gridDifference,
			 	Solution *result,
				SolutionFactory *factory)
{
	Integer i;

	if(N==0)
	{ initialGuess->copy(result);
	  return;
	}

	if(N==1)
	{
      	  
          iterationStep->doIterationStep(initialGuess,gridDifference,result);
	  return;
	}

	CounterCondition counter(N-1);

	performIterationStepsUntil(	&counter,
					iterationStep,
					initialGuess,
					gridDifference,
					result,
					factory);

/*	Solution *x,*y,*src,*dst,*tmp;

	x=factory->createSolution(initialGuess->getGrid());
	y=result; //initialGuess->factory(m_grids[level]);

	src=x;
	dst=y;	

	initialGuess->copy(src);

	for(i=0;i<N;i++)
	{
		iterationStep->doIterationStep(src,gridDifference,dst);
		tmp = src; src=dst; dst=tmp;
	}

	if(src==result) NULL_DELETE(dst);
	else
	{  src->copy(result);
	   NULL_DELETE(src);	
	}
*/
}
