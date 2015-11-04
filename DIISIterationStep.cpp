#include "DIISIterationStep.h"

#include "Settings.h"

#include "copySubMatrix.h"
#include "Solution.h"
#include "Grid.h"

#include "solveLinearSystem.h"
#include "Operator.h"
#include "TextLog.h"
#include "cond.h"


DIISIterationStep::DIISIterationStep(
				Integer NDIIS,
				Operator *oper,
				void (*add)(Solution *,Solution *),
				void (*sub)(Solution *,Solution *),
				void (*mulScalar)(Solution *,Real),
				Real (*scalarProd)(Solution *,Solution *),
				SolutionFactory *solutionFactory,
				Grid *grid,
				Integer maxSkipCount
			)
{	Integer i;

	m_maxSkipCount = maxSkipCount;
	m_skipCount=0;
	m_NDIIS = NDIIS;
	m_oper = oper;
	m_scalarProd = scalarProd;
	m_solutionFactory = solutionFactory;

	m_add = add;
	m_sub = sub;
	m_mulScalar = mulScalar;

	m_deltaVector = new CycledMatrix<Solution *>(m_NDIIS,1);
	m_solutionVector = new CycledMatrix<Solution *>(m_NDIIS,1);

	m_alpha = new SimpleMatrix<Real>(0,0,m_NDIIS+1,1);

	for(i=0;i<m_NDIIS;i++)
	{
		Solution *tmp = m_solutionFactory->createSolution(grid);
		m_deltaVector->setAt(i,0,tmp);

		tmp = m_solutionFactory->createSolution(grid);
		m_solutionVector->setAt(i,0,tmp);
	}

	m_deltaProducts = new CycledMatrix<Real>(m_NDIIS,m_NDIIS);
	m_LHS = new SimpleMatrix<Real>(0,0,m_NDIIS+1,m_NDIIS+1);
	m_RHS = new SimpleMatrix<Real>(0,0,m_NDIIS+1,1);

	m_lastGridDifference = m_solutionFactory->createSolution(grid);
	
	m_skipMatrixShift = 0;
	m_n = 0;

}

DIISIterationStep::~DIISIterationStep()
{
	NULL_DELETE(m_deltaProducts);
	NULL_DELETE(m_LHS);
	NULL_DELETE(m_RHS);
	NULL_DELETE(m_lastGridDifference);

	NULL_DELETE(m_alpha);

	Integer i;
	for(i=0;i<m_NDIIS;i++)
	{
		DELETE(m_deltaVector->getAt(i,0))
		DELETE(m_solutionVector->getAt(i,0))
	}

	NULL_DELETE(m_deltaVector);
	NULL_DELETE(m_solutionVector);
}

void DIISIterationStep::doIterationStep(Solution *guess,Solution *gridDifference, Solution *result)
{
	TextLog *log = TextLog::getInstance();

	updateGridDifference(gridDifference);

	nextDelta(guess,result,gridDifference); // result = Fx + GD
	calculateDeltaProducts();
	prepareLHS();
	
	log->printString(3,"LHS=\n");
	log->printMatrix(3,m_LHS);

	prepareRHS();
	

	solve();

	if(!m_skipMatrixShift)
	{	log->printString(3,"alpha=");
		log->printArrayH(3,m_alpha->getRawData(),m_n);
	}

	log->printString(3,"skipMatrixShift=");
	log->printDouble(3,m_skipMatrixShift);

	if(m_skipMatrixShift || m_n<2 ) return; // result = Fx + GD

	constructResult(result,gridDifference);

}

				// thus should not shift the product matrix next time

void DIISIterationStep::updateGridDifference(Solution *gridDifference)
{
	m_sub(m_lastGridDifference,gridDifference); // m_lastGridDifference -= gridDifference
						    // m_lastGridDifference = d1 - d2

	Real d = m_scalarProd(m_lastGridDifference,m_lastGridDifference);

	if(d==0) 
	{
		gridDifference->copy(m_lastGridDifference);
		return;
	}

#if USE_DIIS_updateGridDifferece
	// x_i = Fx_i + d1 + delta1[i]
	// x_i = Fx_i + d2 + delta2[i] 
	// delta2[i] = delta1[i] + d1-d2. 
	// now: d1-d2 = m_lastGridDifference
	
	Integer i;
	for(i=0;i<m_deltaVector->getNumRows(); i++)
	{
		m_add(m_deltaVector->getAt(i,0),m_lastGridDifference);
	}
	
#else
	//reset();
	m_deltaVector->reset();
	m_solutionVector->reset();
	m_deltaProducts->reset();
	m_n=0;
#endif

	gridDifference->copy(m_lastGridDifference);
}

void DIISIterationStep::nextDelta(Solution *x,Solution *result,Solution *gridDifference)
{

	m_oper->F(x,result);  // result = Fx
	m_add(result,gridDifference); // result = Fx + GD

	if(!m_skipMatrixShift)	
	{
		m_deltaVector->nextRow();
		m_solutionVector->nextRow();
		m_deltaProducts->nextRow();
		m_deltaProducts->nextCol();
	}

	m_n = m_deltaProducts->getNumRows();

	x->copy(m_solutionVector->getAt(m_n-1,0));
	

	x->copy(m_deltaVector->getAt(m_n-1,0));   //  delta[n-1] = x
	m_sub(m_deltaVector->getAt(m_n-1,0),result);   // delta[n-1] = x - Fx - GD
	// x = Fx  + GD + delta  => delta = x - Fx - GD
}

void DIISIterationStep::calculateDeltaProducts()
{
	Integer i;
	for(i=0;i<m_n;i++)
	{
		Real a_in = m_scalarProd
				(	m_deltaVector->getAt(m_n-1,0), 
					m_deltaVector->getAt(i,0)
				);
		m_deltaProducts->setAt(i,m_n-1,a_in);
		m_deltaProducts->setAt(m_n-1,i,a_in);
	}
}

void DIISIterationStep::prepareLHS()
{

m_LHS->setNumRows(m_n+1);
m_LHS->setNumCols(m_n+1);
	
copySubMatrix(	m_deltaProducts,//Matrix<T> *src,
		0,		//Integer src_row,
		0,		//Integer src_col,
		m_LHS,		//Matrix<T> *dst,
		0,		//Integer dst_row,
		0,		//Integer dst_col,
		m_n,		//Integer nrow,
		m_n		//Integer ncol
		);
Integer i;
for(i=0;i<m_n;i++)
{
	m_LHS->setAt(i,m_n,-1);
	m_LHS->setAt(m_n,i,1);
//	m_LHS->setAt(i,i,m_LHS->getAt(i,i)+1e-9);
}

m_LHS->setAt(m_n,m_n,0);
}

void DIISIterationStep::prepareRHS()
{
m_RHS->setNumRows(m_n+1);
m_RHS->setNumCols(1);

Integer i;
for(i=0;i<m_n;i++)
	m_RHS->setAt(i,0,0);

m_RHS->setAt(m_n,0,1);
}

void DIISIterationStep::solve()
{
	m_alpha->setNumRows(m_n+1);
	m_alpha->setNumCols(1);

Integer result =
	solveLinearSystem(	m_LHS,	//Matrix<Real> *A,
				m_RHS,	//Matrix<Real> *B,
				m_alpha	//Matrix<Real> *X
			);


	double C = cond(m_deltaProducts);
	
	printf("\nCOND = %le\n",C);

	if(C>MAX_COND) 
	{
		m_skipMatrixShift = 1;
		m_skipCount++;

		if(m_skipCount > m_maxSkipCount)
		{
		//	m_skipCount=0;
		//	m_skipMatrixShift = 0;
		//	reset();
		}
	}
	else
	{
		m_skipMatrixShift = 0;
		m_skipCount = 0;
	}

}

void DIISIterationStep::reset()
{

	Solution *solution = m_solutionVector->getAt(m_n-1,0);
	Solution *delta = m_deltaVector->getAt(m_n-1,0);
	Real deltaProd = m_deltaProducts->getAt(m_n-1,m_n-1);

	m_deltaVector->reset();	
	m_deltaVector->nextRow();
	delta->copy(m_deltaVector->getAt(0,0));

	m_solutionVector->reset();
	m_solutionVector->nextRow();
	solution->copy(m_solutionVector->getAt(0,0));

	m_deltaProducts->reset();
	m_deltaProducts->nextRow();
	m_deltaProducts->nextCol();
	m_deltaProducts->setAt(0,0,deltaProd);

	m_alpha->setAt(0,0,1);
	m_n = 1;
}

void DIISIterationStep::constructResult(Solution *result,Solution *gridDifference)
{
	result->setZero();

	Solution *tmp = m_solutionFactory->createSolution(result->getGrid());
	Integer i;
	for(i=0;i<m_n;i++)
	{
		m_solutionVector->getAt(i,0)->copy(tmp);
		m_mulScalar(tmp,m_alpha->getAt(i,0));
		m_add(result,tmp);
	}
	
	NULL_DELETE(tmp);
}



