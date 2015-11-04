#ifndef PerformIterationStepsWhile_h
#define PerformIterationStepsWhile_h

class Condition;
class Solution;
class IterationStep;
class SolutionFactory;

void performIterationStepsUntil(Condition *condition,
				IterationStep *iterationStep,
			    	Solution *initialGuess, 
			    	Solution *gridDifference,
			 	Solution *result,
				SolutionFactory *factory);

#endif
