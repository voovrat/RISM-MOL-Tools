#ifndef performNIterationSteps_h
#define performNIterationSteps_h

//#include "IterationStep.h"

class IterationStep;
class Solution;
class SolutionFactory;

//Performs N iteration steps
void performNIterationSteps(	Integer N,
			    	IterationStep *iterationStep,
			    	Solution *initialGuess, 
			    	Solution *gridDifference,
			 	Solution *result,
				SolutionFactory *);


#endif
