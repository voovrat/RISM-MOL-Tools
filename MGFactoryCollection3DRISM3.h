#ifndef MGFactoryCollection3DRISM3_h
#define MGFactoryCollection3DRISM3_h

#include "MGFactoryCollection.h"

class ClosureFactory3DRISM;
class DoubleParameter;
class MixingRules;
class DoubleParameter;
class ParametersAdaptor3DRISM;
class IterationStepFactory;
class SolverFactroy;


class MGFactoryCollection3DRISM3 : public MGFactoryCollection
{

public:
 // factories inherited from MGFactoryCollection

public:
	ClosureFactory3DRISM *m_closureFactory;
	DoubleParameter *m_lambdaParameter;
	Real m_lambdaValue;
	MixingRules *m_mixingRules;

protected:
	
	DoubleParameter *createLambda(ParametersAdaptor3DRISM *params);
	DoubleParameter *getLambda(ParametersAdaptor3DRISM *params)
	{
		if(!m_lambdaParameter) 
			m_lambdaParameter = createLambda(params);
		return m_lambdaParameter;
	}

	GridIndependentData *createGridIndependent(ParametersAdaptor3DRISM *params);
	GridIndependentData *getGridIndependent(ParametersAdaptor3DRISM *params)
	{
		if(!m_gridIndependent) 
			m_gridIndependent = createGridIndependent(params);

		return m_gridIndependent;
	}

	OperatorFactory * createOperatorFactory(ParametersAdaptor3DRISM *params);
	OperatorFactory * getOperatorFactory(ParametersAdaptor3DRISM *params)
	{
		if(!m_operatorFactory) 
			m_operatorFactory = createOperatorFactory(params);

		return m_operatorFactory;
	}	


	IterationStepFactory *createFineGridIterationStepFactory(ParametersAdaptor3DRISM *params);
	IterationStepFactory *getFineGridIterationStepFactory(ParametersAdaptor3DRISM *params)
	{
		if(!m_fineGridStepFactory)
			m_fineGridStepFactory = createFineGridIterationStepFactory(params);
	
		return m_fineGridStepFactory;
	}

	IterationStepFactory *createCoarseGridIterationStepFactory(ParametersAdaptor3DRISM *params);
	IterationStepFactory *getCoarseGridIterationStepFactory(ParametersAdaptor3DRISM *params)
	{
		if(!m_coarseGridStepFactory)
			m_coarseGridStepFactory = createCoarseGridIterationStepFactory(params);
	
		return m_coarseGridStepFactory;
	}

	SolverFactory *createCoarseGridSolverFactory(ParametersAdaptor3DRISM *params);
	SolverFactory *getCoarseGridSolverFactory(ParametersAdaptor3DRISM *params)
	{
		if(!m_coarseGridSolverFactory)
			m_coarseGridSolverFactory = createCoarseGridSolverFactory(params);

		return m_coarseGridSolverFactory;
	}

	SolutionFactory *createSolutionFactory(ParametersAdaptor3DRISM *params);
	SolutionFactory *getSolutionFactory(ParametersAdaptor3DRISM *params)
	{
		if(!m_solutionFactory)
			m_solutionFactory = createSolutionFactory(params);

		return m_solutionFactory;
	}	

	ClosureFactory3DRISM 	*createClosureFactory(ParametersAdaptor3DRISM *params);	
	ClosureFactory3DRISM 	*getClosureFactory(ParametersAdaptor3DRISM *params)
	{
		if(!m_closureFactory)
			m_closureFactory = createClosureFactory(params);
	
		return m_closureFactory;
	}

	MixingRules 	*createMixingRules(ParametersAdaptor3DRISM *params);	
	MixingRules 	*getMixingRules(ParametersAdaptor3DRISM *params)
	{
		if(!m_mixingRules)
			m_mixingRules = createMixingRules(params);
	
		return m_mixingRules;
	}	


public:

	MGFactoryCollection3DRISM3();

	void init(ParametersAdaptor3DRISM *params );
	void uninit();

	virtual ~MGFactoryCollection3DRISM3()
	{
		uninit();	
	}

};


#endif
