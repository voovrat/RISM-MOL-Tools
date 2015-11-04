#include "GridComparator1DRISM.h"
#include "Exception.h"

GridComparator1DRISM *GridComparator1DRISM::getInstance()
{
	static GridComparator1DRISM *instance=NULL;
	if(!instance)
		instance = new GridComparator1DRISM();
	return instance;
}


bool GridComparator1DRISM::isLess(const Grid *a,const Grid *b)
{
 const Grid1DRISM *g1 = dynamic_cast<const Grid1DRISM *>(a);
 const Grid1DRISM *g2 = dynamic_cast<const Grid1DRISM *>(b);

 if(!g1 || !g2)
	throw new Exception(this,"GridComparator1DRISM:isLess : invalid parameter class");


	if(g1->getN()<g2->getN()) return true;
	if(g1->getN()>g2->getN()) return false;

	if(g1->getDR()<g2->getDR()) return true;
	if(g1->getDR()>g2->getDR()) return false;

	return false;
}
