#include "GridComparator3DRISM.h"
#include "Exception.h"

GridComparator3DRISM *GridComparator3DRISM::getInstance()
{
	static GridComparator3DRISM *instance=NULL;
	if(!instance)
		instance = new GridComparator3DRISM();
	return instance;
}


bool GridComparator3DRISM::isLess(const Grid *a,const Grid *b)
{
 const Grid3DRISM *g1 = dynamic_cast<const Grid3DRISM *>(a);
 const Grid3DRISM *g2 = dynamic_cast<const Grid3DRISM *>(b);

 if(!g1 || !g2)
	throw new Exception(this,"GridComparator3DRISM:isLess : invalid parameter class");



	if(g1->getNx()<g2->getNx()) return true;
	if(g1->getNx()>g2->getNx()) return false;

	if(g1->getNy()<g2->getNy()) return true;
	if(g1->getNy()>g2->getNy()) return false;

	if(g1->getNz()<g2->getNz()) return true;
	if(g1->getNz()>g2->getNz()) return false;

	if(g1->getDRx()<g2->getDRx()) return true;
	if(g1->getDRx()>g2->getDRx()) return false;

	if(g1->getDRy()<g2->getDRy()) return true;
	if(g1->getDRy()>g2->getDRy()) return false;

	if(g1->getDRz()<g2->getDRz()) return true;
	if(g1->getDRz()>g2->getDRz()) return false;

	return false;
}
