#include "Solution3DRISMR.h"

//#include "mex.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#if DEBUG_LEAKS
TraceAllocations	Solution3DRISMR::m_traceAllocations("Solution3DRISMR","leaks.txt");
#endif


#define Solution3DRISMRBinaryOperation(fnname,operation) \
	SolutionBinaryOperation(fnname,Solution3DRISMR,Real,operation)

#define Solution3DRISMRScalarOperation(fnname,operation) \
	SolutionScalarOperation(fnname,Solution3DRISMR,Real,Real,operation)

#define Solution3DRISMRUnaryOperation(fnname,operation) \
	SolutionUnaryOperation(fnname,Solution3DRISMR,Real,operation)

Solution3DRISMRBinaryOperation(addSolution3DRISMR,*dst+=*src)
Solution3DRISMRBinaryOperation(subSolution3DRISMR,*dst-=*src)
Solution3DRISMRBinaryOperation(mulSolution3DRISMR,*dst*=*src)
Solution3DRISMRBinaryOperation(divSolution3DRISMR,*dst/=*src)

Solution3DRISMRScalarOperation(addScalarSolution3DRISMR,*dst+=lambda)
Solution3DRISMRScalarOperation(subScalarSolution3DRISMR,*dst-=lambda)
Solution3DRISMRScalarOperation(mulScalarSolution3DRISMR,*dst*=lambda)
Solution3DRISMRScalarOperation(divScalarSolution3DRISMR,*dst/=lambda)

Solution3DRISMRUnaryOperation(expSolution3DRISMR,*dst=exp(*dst))


  





