#ifndef MDIISIterationStep_h
#define MDIISIterationStep_h

#include "DIISIterationStep.h"

class Solution;
class SolutionFactory;
class Operator;
class Grid;

#include "Operator.h"
#include "SimpleMatrix.h"
#include "CycledMatrix.h"
#include "GridDependentData.h"

//  Let we are solving x=Fx+gridDifference
//  
//  Let for i=1:n   x_i=F(x_i) + gridDifference + delta[i]
//  We are looking for x_(n+1) = sum alpha[i]*x_i, s.t.
//   (delta[n+1])^2 -> min
//
//   After linearizing the system, we have delta[n+1] = sum delta[i] and
// 
//   (delta[n+1])^2 = sum sum alpha[i]alpha[j] < delta[i] ; delta[j] >
//   where <f;g> means scalar product
//
//   Introducing consition sum alpha[i] = 1 and using Legandre multiplier 2*lambda we have:
//
//    sum sum alpha[i]alpha[j] <delta[i] ; delta[j]> - 2*lambda (sum alpha[i] -1) -> min
//
//   Taking derivatices w.r.t alpha[i] and lambda we obtain the system:
//
//   LHS * Alpha = RHS,
//
// where 
//	 	[  <delta[1];delta[1]> 	... <delta[1];delta[n]>		-1  ]
//		[  ...				...	    		... ]	
// /LHS= 	[  <delta(n);delta(1)> 	... <delta[n];delta[n]> 	-1  ]
//		[   1			...	   1		 	 0  ]
//
// RHS = [ 0, ... , 0, 1]^T
//
// Alpha = [ alpha[1] ... alpha[n], lambda ]^T
//

// DISCLAIMER:
// This code is NOT the fastest one...
// But.. i tried to make it understandable...
// Reasons, why efficiency here is not so important:
//   Typical size of solution in 3DRISM is 128x128x128 = 2M.
//   Typical NDIIS=10. 
// Thus, in DIIS we deal with matrices of size 10x10, 
// but the most time is spent to calculate scalar product of size 2M.
// Thus, operations with matrices 10x10 can be not so efficient - but understandable


// in MDIIS we add:

// let x[n+1] = sum alpha[i]*x[i]
//
// result = (1-mu) * x[n+1] + mu * ( F(x[n+1]) + D)

class MDIISIterationStep : public DIISIterationStep
{
protected:
	Real m_preDamping,m_postDamping;

	virtual void solve();
	virtual void constructResult(Solution *result,Solution *gridDifference);

public:
	MDIISIterationStep(	Integer NDIIS,
				Operator *oper,
				void (*add)(Solution *,Solution *),
				void (*sub)(Solution *,Solution *),
				void (*mulScalar)(Solution *,Real),
				Real (*scalarProd)(Solution *,Solution *),
				SolutionFactory *solutionFactory,
				Grid *grid,
				Integer maxSkipCount=DIIS_MAX_SKIP_COUNT,
				Real preDamping = DIIS_PRE_DAMPING,
				Real postDamping = DIIS_POST_DAMPING
			)
	: DIISIterationStep(	NDIIS,		//Integer NDIIS,
				oper,		//Operator *oper,
				add,		//void (*add)(Solution *,Solution *),
				sub,		//void (*sub)(Solution *,Solution *),
				mulScalar,	//void (*mulScalar)(Solution *,Real),
				scalarProd,	//Real (*scalarProd)(Solution *,Solution *),
				solutionFactory,//SolutionFactory *solutionFactory,
				grid,		//Grid *grid,
				maxSkipCount	//Integer maxSkipCount=10,
			) 
	{
		m_preDamping = preDamping;
		m_postDamping = postDamping;
	}

	virtual ~MDIISIterationStep() {}



};

class MDIISIterationStepFactory : public IterationStepFactory
{
protected:
	
	Integer m_NDIIS;
	void (*m_add)(Solution *,Solution *);
	void (*m_sub)(Solution *,Solution *);
	void (*m_mulScalar)(Solution *,Real);
	Real (*m_scalarProd)(Solution *,Solution *);
	SolutionFactory *m_solutionFactory;

	Integer m_maxSkipCount;
	Real m_preDamping,m_postDamping;

public:

	MDIISIterationStepFactory(
			Integer NDIIS,
			void (*add)(Solution *,Solution *),
			void (*sub)(Solution *,Solution *),
			void (*mulScalar)(Solution *,Real),
			Real (*scalarProd)(Solution *,Solution *),
			SolutionFactory *solutionFactory,
			Integer maxSkipCount = DIIS_MAX_SKIP_COUNT,
			Real preDamping = DIIS_PRE_DAMPING,
			Real postDamping = DIIS_POST_DAMPING
		)
	{
		m_NDIIS = NDIIS;
		m_add = add;
		m_sub = sub;
		m_mulScalar = mulScalar;
		m_scalarProd = scalarProd;
		m_solutionFactory = solutionFactory;
		m_maxSkipCount = maxSkipCount;
		m_preDamping = preDamping;
		m_postDamping = postDamping;
	}

	IterationStep *createIterationStep(Operator *oper)
	{
		Grid *grid = oper->getGridDependent()->getGrid();

		return new MDIISIterationStep(
				m_NDIIS,	//Integer NDIIS,
				oper,		//Operator *oper,
				m_add,		//void (*add)(Solution *,Solution *),
				m_sub,		//void (*sub)(Solution *,Solution *),
				m_mulScalar,	//void (*mulScalar)(Solution *,Real),
				m_scalarProd,	//Real (*scalarProd)(Solution *,Solution *),
				m_solutionFactory,//SolutionFactory *solutionFactory,
				grid,		 //Grid *grid
				m_maxSkipCount,	//Integer maxSkipCount=DIIS_MAX_SKIP_COUNT,
				m_preDamping,
				m_postDamping	//Real DIIS_damping=DIIS_DAMPING
		);
	}

};


#endif
