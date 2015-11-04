#ifndef readDoubleTableSimple_h
#define readDoubleTableSimple_h

#include "Settings.h"

void readDoubleTableSimple(	const char *fname,
			Integer *Nrow,	//out
			Integer *Ncol,	//out
			Real **result //out, will be allocated
			);

#endif
