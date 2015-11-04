#include "Grid1DRISM.h"

void restrictGrid1DRISM(Grid *src,Grid *result)
{
	Grid1DRISM *goodSrc;
	Grid1DRISM *goodDst;

	goodSrc = dynamic_cast<Grid1DRISM*>(src);
	if(!goodSrc) 
		throw "restictGrid1DRISM: invalid class of src; should be Grid1DRISM";

	goodDst = dynamic_cast<Grid1DRISM*>(result);
	if(!goodDst) 
		throw "restictGrid1DRISM: invalid class of dst; should be Grid1DRISM";	

	goodDst->m_N = goodSrc->m_N/2;
	goodDst->m_dR = goodSrc->m_dR*2;
	goodDst->m_dK = Grid1DRISM::calcDK(goodDst->m_N,goodDst->m_dR);
}

void interpolateGrid1DRISM(Grid *src,Grid *result)
{
	Grid1DRISM *goodSrc;
	Grid1DRISM *goodDst;

	goodSrc = dynamic_cast<Grid1DRISM*>(src);
	if(!goodSrc) 
		throw "interpolateGrid1DRISM: invalid class of src; should be Grid1DRISM";

	goodDst = dynamic_cast<Grid1DRISM*>(result);
	if(!goodDst) 
		throw "interpolateGrid1DRISM: invalid class of dst; should be Grid1DRISM";	

	goodDst->m_N = goodSrc->m_N*2;
	goodDst->m_dR = goodSrc->m_dR/2;
	goodDst->m_dK = Grid1DRISM::calcDK(goodDst->m_N,goodDst->m_dR);
}

void extendGrid1DRISM(Grid *src,Grid *result)
{
	Grid1DRISM *goodSrc;
	Grid1DRISM *goodDst;

	goodSrc = dynamic_cast<Grid1DRISM*>(src);
	if(!goodSrc) 
		throw "extendGrid1DRISM: invalid class of src; should be Grid1DRISM";

	goodDst = dynamic_cast<Grid1DRISM*>(result);
	if(!goodDst) 
		throw "extendGrid1DRISM: invalid class of dst; should be Grid1DRISM";	

	goodDst->m_N = goodSrc->m_N*2;
	goodDst->m_dR = goodSrc->m_dR;
	goodDst->m_dK = Grid1DRISM::calcDK(goodDst->m_N,goodDst->m_dR);

}
