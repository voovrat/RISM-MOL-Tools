#ifndef readDoubleTable_h
#define readDoubleTable_h

#include "Settings.h"

void readDoubleTable(	const char *fname,
			Integer *Nrow,	//out
			Integer *Ncol,	//out
			Real **result //out, will be allocated
			);

#endif
