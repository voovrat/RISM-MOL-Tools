#ifndef GridIndependentData_h
#define GridIndependentData_h

class GridDependentData;
class Grid;

// Grid Independent Data. Data, which is used for the calculation iterative operator (see Operator.h), which does not depend on the grid.
// In the case of RISM grid dependent are:
//   - coordinantes, partial charges, LJ parameters, distances between atoms and so on

#include "Object.h"

class GridIndependentData : public Object
{
  public: 

     virtual ~GridIndependentData() {}
     virtual GridDependentData *createGridDependent(Grid *)=0;

};

#endif
