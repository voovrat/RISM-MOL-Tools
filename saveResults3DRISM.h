#ifndef saveResults3DRISM_h
#define saveResults3DRISM_h

class Solution3DRISMR;

void saveResults3DRISM(	Solution3DRISMR *gamma,
			Solution3DRISMR *c,
			Solution3DRISMR *clong,
			Solution3DRISMR *g,
			Solution3DRISMR *minusBetaUshort,
			const char *prefix,
			const char *suffix
		);

#endif
