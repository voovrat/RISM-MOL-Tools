#ifndef mulSolutionByChiMatrix2_h
#define mulSolutionByChiMatrix2_h

class Solution3DRISMK;
class SiteMultiplicities;

void mulSolutionByChiMatrix2(	Solution3DRISMK *solution,
				SiteMultiplicities *,
				Solution3DRISMK ***chiIndex,
				Real **chiMultipliers,
				Solution3DRISMK *result
			);


#endif
