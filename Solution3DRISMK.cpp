#include "Solution3DRISMK.h"

//#include "mex.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "Solution3DRISMOperation.h"

#if DEBUG_LEAKS
TraceAllocations	Solution3DRISMK::m_traceAllocations("Solution3DRISMK","leaks.txt");
#endif


#define Solution3DRISMKBinaryOperation(fnname,operation) \
	SolutionBinaryOperation(fnname,Solution3DRISMK,complex<Real>,operation)
				       
#define Solution3DRISMKScalarOperation(fnname,operation) \
	SolutionScalarOperation(fnname,Solution3DRISMK,complex<Real>,Real,operation)

Solution3DRISMKBinaryOperation(addSolution3DRISMK,*dst+=*src)
Solution3DRISMKBinaryOperation(subSolution3DRISMK,*dst-=*src)
Solution3DRISMKBinaryOperation(mulSolution3DRISMK,*dst*=*src)
Solution3DRISMKBinaryOperation(divSolution3DRISMK,*dst/=*src)

Solution3DRISMKScalarOperation(addScalarSolution3DRISMK,*dst+=lambda)
Solution3DRISMKScalarOperation(subScalarSolution3DRISMK,*dst-=lambda)
Solution3DRISMKScalarOperation(mulScalarSolution3DRISMK,*dst*=lambda)
Solution3DRISMKScalarOperation(divScalarSolution3DRISMK,*dst/=lambda)





