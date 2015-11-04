#ifndef MultiGridInterface_h
#define MultiGridInterface_h

#include "Object.h"

class Grid3DRISM;
class BlackBoxSolver;
class Solution3DRISMR;
class SolutionFactory3DRISMR;
class ParametersAdaptor3DRISM;
class GridDependentNormFactory;
class BlackBoxSolverFactory;
class GridDependentNormFactory;

#include "Operations.h"
#include "MGFactoryCollection3DRISM3.h"


class MultiGridInterface : public Object
{
protected:
	Grid3DRISM *m_inputGrid,*m_outputGrid;
	BlackBoxSolver *m_solver;
	Solution3DRISMR *m_gamma,*m_c,*m_g,*m_clong,*m_minusBetaUshort;
	ParametersAdaptor3DRISM *m_params;
	SolutionFactory3DRISMR *m_solutionFactory;

	MGFactoryCollection3DRISM3 m_factories;
	Operations m_operations;

	void initOperations(Operations *operations);
	void initInputGrid();

	GridDependentNormFactory *createVerboseNormFactory();

	BlackBoxSolverFactory *createMultiGridSolverFactory(GridDependentNormFactory *verboseNormFactory);
	BlackBoxSolverFactory *createPlainSolverFactory(GridDependentNormFactory *verboseNormFactory);
	BlackBoxSolverFactory *createNestedSolverFactory(GridDependentNormFactory *verboseNormFactory,Integer MultiGrid = 1);

	char m_prefix[256];
	void getPrefix();

public:
	MultiGridInterface(ParametersAdaptor3DRISM *params);


	virtual ~MultiGridInterface();

	Grid3DRISM *getInputGrid()
	{
		return m_inputGrid;
	}
	
	Grid3DRISM *getOutputGrid()
	{
		return m_inputGrid;
	}	

	BlackBoxSolver *getSolver()
	{
		return m_solver;
	}

	void init();
	void solve();
	void solve(Solution3DRISMR *initialGuess);
	void saveResults();
	void saveFreeEnergies();

	Solution3DRISMR *getGamma()
	{
		return m_gamma;
	}

	Solution3DRISMR *getC()
	{
		return m_c;
	}

	Solution3DRISMR *getG()
	{
		return m_g;
	}

	Solution3DRISMR *getCLong()
	{
		return m_clong;
	}

	Solution3DRISMR *getMinusBetaUshort()
	{
		return m_minusBetaUshort;
	}
	

};

#endif
