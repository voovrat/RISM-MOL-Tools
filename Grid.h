#ifndef Grid_h
#define Grid_h

// class Contain information about the grid
// because grids can be different (1D,3D, irregular, etc), here only interface is specified.
// Concrete Grid classes should be derived from this one. 
// Derived classes should satisfy the interface:
// One should be able - to restrict grid, interpolate grid, extend grid.
// These functions are used while the initializing the MultiGrid algorithm
//
// Class is supposed to contain few members. (e.g. N,dR).

#include "Object.h"

class Grid;

class Grid : public Object
{
public:
	Grid() {}
 	virtual ~Grid() {}

  // copy grid to the given destination.
  // function does not allocate the memory. 
  // result should be allocated before.   
 	virtual void copy(Grid *result) const=0;

  // creates an empty solution of derived class.
  // typical implementation: 
  //  class G: Grid { ... };
  //  G::factory() {return new G;}
 	virtual Grid *factory() const=0;

 	virtual Integer isEqual(const Grid *) const=0;

   //creates a new Grid object and copies there the existing one
	Grid *clone() const
	{  Grid *r = factory();
	copy(r); 
	return r;
	}
};

#endif
