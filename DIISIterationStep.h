#ifndef DIISIterationStep_h
#define DIISIterationStep_h

#include "IterationStep.h"

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

class DIISIterationStep : public IterationStep
{
protected:

	Integer m_NDIIS;
	CycledMatrix<Solution *> *m_deltaVector;// NDIIS x 1
						// delta[i] = Fx_i - x_i - gridDifference, 
						// where equation to solve is: x=Fx+gridDifference

	CycledMatrix<Solution *> *m_solutionVector;// NDIISx1, solutions x[1]...x[n]


	CycledMatrix<Real> 	 *m_deltaProducts; // NDIIS x NDIIS
					// deltaProcuct[i,j] = ( delta[i], delta[j] )
		

	SimpleMatrix<Real> 	*m_LHS;	
		//(NDIIS+1)x(NDIIS+1)
		// 	[  deltaProduct(1,1) ... deltaProcuct(1,n)  -1  ]
		//	[  ...				...	    ... ]	
		//LHS=  [  deltaProduct(n,1) ... deltaProduct(n,n)  -1  ]
		//      [   1		....	   1		     0  ]

	SimpleMatrix<Real> 	*m_alpha;// Alpha = [ alpha[1] ... alpha[n], lambda ]^T


	SimpleMatrix<Real>	*m_RHS; //(NDIIS+1)x1, RHS = [ 0, ... ,0, 1]^T


	Real (*m_scalarProd)(Solution *,Solution *);
	void 	(*m_add)(Solution *,Solution *);
	void	(*m_sub)(Solution *,Solution *);
	void 	(*m_mulScalar)(Solution *,Real);
	
	Solution *m_lastGridDifference;

	Integer m_skipMatrixShift;	// if previous matrix was singular, we do not consider the last vecto
				// thus should not shift the product matrix next time

	Operator *m_oper;

	Integer m_n;
	Integer m_skipCount;
	Integer m_maxSkipCount;

	virtual void updateGridDifference(Solution *gridDifference);

	virtual void nextDelta(Solution *guess,Solution *result,Solution *gridDifference);
	virtual void calculateDeltaProducts();
	virtual void prepareLHS();
	virtual void prepareRHS();
	virtual void solve();
	virtual void constructResult(Solution *result,Solution *gridDifference);
	virtual void reset();	// copy n-th vector to 1st and set NVector=1;

	SolutionFactory *m_solutionFactory;


public:
	DIISIterationStep(	Integer NDIIS,
				Operator *oper,
				void (*add)(Solution *,Solution *),
				void (*sub)(Solution *,Solution *),
				void (*mulScalar)(Solution *,Real),
				Real (*scalarProd)(Solution *,Solution *),
				SolutionFactory *solutionFactory,
				Grid *grid,
				Integer maxSkipCount=10
			);

	virtual ~DIISIterationStep();


	virtual void doIterationStep(Solution *guess,Solution *gridDifference, Solution *result);

};

class DIISIterationStepFactory : public IterationStepFactory
{
protected:
	
	Integer m_NDIIS;
	void (*m_add)(Solution *,Solution *);
	void (*m_sub)(Solution *,Solution *);
	void (*m_mulScalar)(Solution *,Real);
	Real (*m_scalarProd)(Solution *,Solution *);
	SolutionFactory *m_solutionFactory;

public:

	DIISIterationStepFactory(
			Integer NDIIS,
			void (*add)(Solution *,Solution *),
			void (*sub)(Solution *,Solution *),
			void (*mulScalar)(Solution *,Real),
			Real (*scalarProd)(Solution *,Solution *),
			SolutionFactory *solutionFactory
		)
	{
		m_NDIIS = NDIIS;
		m_add = add;
		m_sub = sub;
		m_mulScalar = mulScalar;
		m_scalarProd = scalarProd;
		m_solutionFactory = solutionFactory;
	}

	IterationStep *createIterationStep(Operator *oper)
	{
		Grid *grid = oper->getGridDependent()->getGrid();

		return new DIISIterationStep(
				m_NDIIS,	//Integer NDIIS,
				oper,		//Operator *oper,
				m_add,		//void (*add)(Solution *,Solution *),
				m_sub,		//void (*sub)(Solution *,Solution *),
				m_mulScalar,	//void (*mulScalar)(Solution *,Real),
				m_scalarProd,	//Real (*scalarProd)(Solution *,Solution *),
				m_solutionFactory,//SolutionFactory *solutionFactory,
				grid		 //Grid *grid
		);
	}

};


#endif
