#ifndef Grid1DRISM_h
#define Grid1DRISM_h

#include <math.h>

#include "Grid.h"

// class Contain implementation of the Grid class for 1D regular grid.
// it contains: dR, dk,
//
// Class is supposed to contain few members. (e.g. N,dR).

// restrict the fine grid to coarse one. 
  // function does not allocate the memory. 
  // result should be allocated before.
   void restrictGrid1DRISM(Grid *src,Grid *result);

  // restrict the coarse grid to the fine one. 
  // function does not allocate the memory. 
  // result should be allocated before.
   void interpolateGrid1DRISM(Grid *src,Grid *result);

  // extend the grid to the grid with larger cutoff distance. 
  // function does not allocate the memory. 
  // result should be allocated before.
   void extendGrid1DRISM(Grid *src,Grid *result);


class Grid1DRISM : public Grid
{
  protected:
    	Integer m_N;
	Real m_dR,m_dK;

	friend   void restrictGrid1DRISM(Grid *src,Grid *result);
	friend   void interpolateGrid1DRISM(Grid *src,Grid *result);
	friend   void extendGrid1DRISM(Grid *src,Grid *result);

	static Real calcDK(Real N,Real dR)	
	{
		return M_PI / (N+1) / dR;
	}

  public:

	Grid1DRISM(Integer N,Real dR)
	{
 	  m_N = N; m_dR=dR;
	  m_dK = calcDK(N,dR);
	}
 
	// copy grid to the given destination.
	// function does not allocate the memory. 
	// result should be allocated before.   
	virtual void copy(Grid *result) const
	{
		Grid1DRISM * r = dynamic_cast<Grid1DRISM *>(result);

		if(!r)
			throw "Invalid type of Grid obj: should be Grid1DRISM";		

 		r->m_N = m_N;
		r->m_dR = m_dR;
		r->m_dK = m_dK;
	}

   	Integer getN()	const {return m_N;}
	Real getDR()	const {return m_dR;}
	Real getDK()	const {return m_dK;}	

	virtual Integer isEqual(const Grid *grid) const
	{
		const Grid1DRISM *goodGrid = dynamic_cast<const Grid1DRISM*>(grid);

		if(!goodGrid)
			throw "Grid1DRISM::isEqual : Incorrect object class ";
	
		return goodGrid->m_N==m_N && fabs(goodGrid->m_dR - m_dR)<1e-6;
	}

  // creates an empty solution of derived class.
  // typical implementation: 
  //  class G: Grid { ... };
  //  G::factory() {return new G;}
   virtual Grid *factory() const
	{
		return new Grid1DRISM(0,0);
	}


};

#endif
