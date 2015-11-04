#ifndef Solution3DRISMOperation_h
#define Solution3DRISMOperation_h

#include "Solution.h"

#define Solution3DRISMBinaryOperation(fnname,operation) \
	SolutionBinaryOperation(fnname,Solution3DRISMR,Real,operation)

#define Solution3DRISMScalarOperation(fnname,operation) \
	SolutionScalarOperation(fnname,Solution3DRISMR,Real,Real,operation)

#endif
