#ifndef Operations_h
#define Operations_h

#include "Solution.h"
#include "Grid.h"


// Operations which can be performed on the solution and on the grid.

// TAKE CARE : SOLUTION AND GRID OPERATIONS SHOULD BE CONSISTENT!!!

// They are NOT parts of solution, and solution is independent on 
// the operations which can be done on it
// That's why i put them to the separate struct with function pointers...

typedef void (*BinarySolutionOperation)(Solution *,Solution *);

typedef struct{

        // restrict solution from fine to coarse grid. 
        // function does not allocate the memory. 
        // result should be allocated before.
        // y= restrict(x)
   void (*restrictSolution)(Solution *x,Solution *y);

        // interpolate solution from coarse to fine grid. 
        // function does not allocate the memory. 
        // result should be allocated before.
        // y = interpolate(x);
   void (*interpolateSolution)(Solution *x, Solution *y);
 
        // extend solution to the grid with larger number of points.
        // function does not allocate the memory. 
        // result should be allocated before.
        // y = extend(x);      
   void (*extendSolution)(Solution *x, Solution *y);

	// add two solutions. Data is not alocated in the function.
        // function works as: x = x +y
   void (*add)(Solution *x, Solution *y);    // x = x + y

	// subtract two solutions. Data is not alocated in the function.
        // function works as: x = x -y
   void (*sub)(Solution *x,Solution *y);    // x= x -=y;

 	// multiply solution by the scalar:  x =x*lambda
   void (*mulScalar)(Solution *x,Real lambda);  // x = x * lambda

  // norm. Calculate the norm between two solutions
  // Real (*norm)(Solution *x,Solution *y);    // 


  // restrict the fine grid to coarse one. 
  // function does not allocate the memory. 
  // result should be allocated before.
   void (*restrictGrid)(Grid *src,Grid *result);

  // restrict the coarse grid to the fine one. 
  // function does not allocate the memory. 
  // result should be allocated before.
   void (*interpolateGrid)(Grid *src,Grid *result);

  // extend the grid to the grid with larger cutoff distance. 
  // function does not allocate the memory. 
  // result should be allocated before.
   void (*extendGrid)(Grid *src,Grid *result);

} Operations;



#endif
