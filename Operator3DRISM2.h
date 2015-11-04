#ifndef Operator3DRISM2_h
#define Operator3DRISM2_h

#include "Operator.h"

class SolutionFactory3DRISMR;
class Solution3DRISMR;

class SolutionFactory3DRISMK;
class Solution3DRISMK;

class Grid3DRISM;

class GridDependentInterface3DRISM;
class GridIndependentInterface3DRISM;

class Operator3DRISM2 : public Operator
{
protected:
// inherited	GridIndependentData *m_gridIndependent;
// inherited	GridDependentData *m_gridDependent;

	Grid3DRISM *m_grid;

	SolutionFactory3DRISMR *m_solutionFactoryR;
	SolutionFactory3DRISMK *m_solutionFactoryK;

	GridDependentInterface3DRISM *m_gridDependent3D;
	GridIndependentInterface3DRISM *m_gridIndependent3D;

	Solution3DRISMR *m_cR;
	Solution3DRISMK *m_cK;
	Solution3DRISMK *m_gammaK;

	Integer m_numSolventSites;

	void closure_step(Solution3DRISMR *gamma);
	void fft_step();
	void gamma_step();
	void ifft_step(Solution3DRISMR *result);
	void addTheta_step(Solution3DRISMR *result);

public:

	Operator3DRISM2(GridIndependentInterface3DRISM *gridIndependent,
			GridDependentInterface3DRISM *gridDependent
			);

	virtual ~Operator3DRISM2();

		//real type of arguments should be Solution3DRISMR 
	virtual void F(	Solution *gamma,
			Solution *result	//out
		);		// result = F(gamma)

	Solution3DRISMK *getGammaK()
	{
		return m_gammaK;
	}

	Solution3DRISMR *getCR()
	{
		return m_cR;
	}
	
	Solution3DRISMK *getCK()
	{
		return m_cK;
	}

};

class OperatorFactory3DRISM2 : public OperatorFactory
{
public:

	virtual Operator *createOperator(GridIndependentData *gridIndependent,
					GridDependentData *gridDependent
					);

};


#endif
