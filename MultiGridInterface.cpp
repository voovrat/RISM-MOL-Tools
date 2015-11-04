#include "MultiGridInterface.h"

#include "Grid3DRISM.h"
#include "Solver.h"
#include "Solution3DRISMR.h"
#include "ParametersAdaptor3DRISM.h"
#include "MGFactoryCollection3DRISM3.h"
#include "BlackBoxConditionSolverFactory.h"
#include "GridDependentNormFactory.h"

#include "interpolateSolution3DRISMR.h"
#include "restrictSolution3DRISMR.h"
#include "extendSolution3DRISMR.h"
#include "ParametersAdaptor3DRISM.h"

#include "L2Norm3DRISM.h"
#include "FreeEnergyNorm.h"
#include "HNCFreeEnergy3DRISM.h"
#include "VerboseNorm.h"
#include "SequentialNormCondition.h"
#include "MultiGrid.h"
#include "MultiGridConditionSolver.h"
#include "RealNormCondition.h"
#include "ExtendSolver.h"

#include "ScalProdNormSolution3DRISMR.h"
//#include "GridDependent3DRISM2.h"
#include "GridDependent3DRISM3.h"
#include "Closure3DRISM.h"
#include "strcpyUntil.h"
#include "saveResults3DRISM.h"
#include "GridIndependentInterface3DRISM.h"
#include "GridDependentInterface3DRISM.h"
#include "writeDoubleArrayToFile.h"
#include "SiteDensities.h"

#include "Units.h"
#include "MultiGridInterface.h"

#include "SiteMultiplicities.h"
#include "StatisticsBlackBoxSolverWrapper.h"
#include "Statistics.h"

//#include "NestedMultiGridSolver.h"
#include "NestedSolver.h"
#include "NestedSolverSubFactory.h"
#include "NestedMultiGridSubFactory.h"
#include "NestedPlainSubFactory.h"


#include "GridNumerator.h"
#include "ExtendGridNumeratorFactory.h"
#include "ExtendGrid.h"
#include "ExtendSolution3DRISM.h"

#include "CombinedSolverFactory.h"

#include "GridIndependent3DRISM3.h"
#include "LongSiteSitePotential.h"
#include "buildPotential.h"

void MultiGridInterface::initOperations(Operations *operations)
{
	operations->restrictSolution = &restrictSolution3DRISMR; 
  	operations->interpolateSolution = &interpolateSolution3DRISMR;  
   	operations->extendSolution = extendSolution3DRISMR; 

	operations->add = &addSolution3DRISMR; 
	operations->sub = &subSolution3DRISMR; 

 	operations->mulScalar = &mulScalarSolution3DRISMR; 
	operations->restrictGrid = &restrictGrid3DRISM;
	operations->interpolateGrid = &interpolateGrid3DRISM; 
	operations->extendGrid = &extendGrid3DRISM; 
}


GridDependentNormFactory *MultiGridInterface::createVerboseNormFactory()
{
	GridDependentNormFactory *fineGridNormFactory;

	if(m_params->getNormType()==ParametersAdaptor3DRISM::L2_NORM)
	{
		fineGridNormFactory = new L2Norm3DRISMFactory(m_solutionFactory
					);
	}
	
	if(m_params->getNormType()==ParametersAdaptor3DRISM::HNC_NORM)
	{
		FreeEnergyFactory *freeEnergyFactory =
		new HNCFreeEnergyFactory3DRISM(m_solutionFactory//,
					//	0 //noBetaU = 0 --> use betaU
						);

		fineGridNormFactory = new FreeEnergyNormFactory(freeEnergyFactory
					);
		fineGridNormFactory->addToDeleteList(freeEnergyFactory);
	}	

	
	VerboseNormFactory *verboseNormFactory
		=new VerboseNormFactory("NormError: ","\n",1,fineGridNormFactory);

	verboseNormFactory->addToDeleteList(fineGridNormFactory);

	return verboseNormFactory;
}


BlackBoxSolverFactory *MultiGridInterface::createMultiGridSolverFactory(GridDependentNormFactory *verboseNormFactory)
{
	//SequentialNormConditionFactory *normConditionFactory =
	//	new SequentialNormConditionFactory(verboseNormFactory,m_params->getTolerance());

	GridDependentNormFactory *fastNormFactory = new ScalProdNormSolution3DRISMRFactory();
	

	RealNormConditionFactory *normConditionFactory =
		new RealNormConditionFactory( 	m_params->getTolerance(),//	Real tolerance,	 
						m_params->getDecayFactor(),//Real decayFactor,	
						fastNormFactory,	//GridDependentNormFactory *fastNormFactory,
						verboseNormFactory,	//GridDependentNormFactory *realNormFactory,
						m_factories.m_solutionFactory,//SolutionFactory *solutionFactory,
						m_params->getGrowFactor() ,	//Real growFactor,
						m_params->getMaxCoarseStepCount(),	//Integer maxCount, 
						m_params->getMinCoarseError(),		//Real minError
						m_params->getFirstGrowFactor()		//first grow error
					);
		
	normConditionFactory->addToDeleteList(fastNormFactory);

	MultiGridIterationStepFactory *multiGridIterationStepFactory=
	new MultiGridIterationStepFactory();


	MultiGridConditionSolverFactory *multiGridConditionSolverFactory
	= new MultiGridConditionSolverFactory
		(	normConditionFactory , //ConditionFactory *condition,
		 	&m_operations,//Operations *operations,
			&m_factories,//MGFactoryCollection *factories,
			m_params->getDepth(),//Integer depth, 
			multiGridIterationStepFactory,	//MultiGridIterationStepFactory *multiGridIterationStepFactory,
			m_params->getNumberOfPreSmoothingSteps(),//Integer preSmoothingSteps=1, 
			m_params->getNumberOfPostSmoothingSteps(),//Integer postSmoothingSteps=0, 
			m_params->getNumberOfMultiGridSubSteps()//Integer numberOfMultiGridSubSteps=1
		);

	multiGridConditionSolverFactory->addToDeleteList(normConditionFactory);

	StatisticsBlackBoxSolverWrapperFactory *wrapperFactory = new StatisticsBlackBoxSolverWrapperFactory(multiGridConditionSolverFactory);
	wrapperFactory->addToDeleteList(multiGridConditionSolverFactory);


	return wrapperFactory;

}


BlackBoxSolverFactory *MultiGridInterface::createPlainSolverFactory(GridDependentNormFactory *verboseNormFactory)
{
	GridDependentNormFactory *fastNormFactory = new ScalProdNormSolution3DRISMRFactory();
	

	RealNormConditionFactory *normConditionFactory =
		new RealNormConditionFactory( 	m_params->getTolerance(),//	Real tolerance,	 
						m_params->getDecayFactor(),//Real decayFactor,	
						fastNormFactory,	//GridDependentNormFactory *fastNormFactory,
						verboseNormFactory,	//GridDependentNormFactory *realNormFactory,
						m_factories.m_solutionFactory,//SolutionFactory *solutionFactory,			
						m_params->getGrowFactor(),	//Real growFactor,
						m_params->getMaxCoarseStepCount(),	//Integer maxCount, 
						m_params->getMinCoarseError(),		//Real minError 
						m_params->getFirstGrowFactor()				
					);
		


	normConditionFactory->addToDeleteList(fastNormFactory);

	BlackBoxSolverFactory *solverFactory= new BlackBoxConditionSolverFactory(
			m_factories.m_gridIndependent, //	GridIndependentData *gridIndependent,
			m_factories.m_operatorFactory,//	OpertorFactory *operatorFactory,
			m_factories.m_coarseGridStepFactory,//IterationStepFactory *iterationStepFactory,
			normConditionFactory,//ConditionFactory *conditionFactory,
			m_factories.m_solutionFactory //		SolutionFactory *solutionFactory
	);

	solverFactory->addToDeleteList(normConditionFactory);

	StatisticsBlackBoxSolverWrapperFactory *wrapperFactory = new StatisticsBlackBoxSolverWrapperFactory(solverFactory);
	wrapperFactory->addToDeleteList(solverFactory);


	return wrapperFactory;

}




BlackBoxSolverFactory *MultiGridInterface::createNestedSolverFactory(GridDependentNormFactory *verboseNormFactory,Integer MultiGrid)
{
	//SequentialNormConditionFactory *normConditionFactory =
	//	new SequentialNormConditionFactory(verboseNormFactory,m_params->getTolerance());

	GridDependentNormFactory *fastNormFactory = new ScalProdNormSolution3DRISMRFactory();
	

	RealNormConditionFactory *fineConditionFactory =
		new RealNormConditionFactory( 	m_params->getTolerance(),//	Real tolerance,	 
						m_params->getDecayFactor(),//Real decayFactor,	
						fastNormFactory,	//GridDependentNormFactory *fastNormFactory,
						verboseNormFactory,	//GridDependentNormFactory *realNormFactory,
						m_factories.m_solutionFactory,//SolutionFactory *solutionFactory,
						m_params->getGrowFactor() ,	//Real growFactor,
						m_params->getMaxCoarseStepCount(),	//Integer maxCount, 
						m_params->getMinCoarseError(),		//Real minError
						m_params->getFirstGrowFactor()		//first grow error
					);
		
	fineConditionFactory->addToDeleteList(fastNormFactory);

	RealNormConditionFactory *coarseConditionFactory =
		new RealNormConditionFactory( 	m_params->getNestedTolerance(),//	Real tolerance,	 
						m_params->getNestedDecayFactor(),//Real decayFactor,	
						fastNormFactory,	//GridDependentNormFactory *fastNormFactory,
						verboseNormFactory,	//GridDependentNormFactory *realNormFactory,
						m_factories.m_solutionFactory,//SolutionFactory *solutionFactory,
						m_params->getNestedGrowFactor() ,	//Real growFactor,
						m_params->getNestedMaxCoarseStepCount(),	//Integer maxCount, 
						m_params->getMinCoarseError(),		//Real minError
						m_params->getFirstGrowFactor()		//first grow error
					);
		
	coarseConditionFactory->addToDeleteList(coarseConditionFactory);

	NestedSolverSubFactory *subFactory;

	if(MultiGrid)
		subFactory = new NestedMultiGridSubFactory(
					&m_operations,	//Operations *operations,
					&m_factories,	//MGFactoryCollection *factories 
					m_params->getNumberOfPreSmoothingSteps(),//Integer preSmoothingSteps=1, 
					m_params->getNumberOfPostSmoothingSteps(),//Integer postSmoothingSteps=0, 
					m_params->getNumberOfMultiGridSubSteps()//Integer numberOfMultiGridSubSteps=1
				);
	else
		subFactory = new NestedPlainSubFactory( &m_operations, &m_factories);



	BlackBoxSolverFactory *nestedSolverFactory = new NestedSolverFactory(
			fineConditionFactory,		//ConditionFactory *fineConditionFactory,
			coarseConditionFactory,		//ConditionFactory *coarseConditionFactory,
			&m_operations,			//Operations *operations,
			&m_factories,			//MGFactoryCollection *factories,
			//GridIndependentData *gridIndependent,
			//Grid	*fineGrid,
			m_params->getDepth(),		//	Integer depth,
			subFactory			//NestedSolverSubFactory *subFactory
			);

	nestedSolverFactory->addToDeleteList(fineConditionFactory);
	nestedSolverFactory->addToDeleteList(coarseConditionFactory);
	nestedSolverFactory->addToDeleteList(subFactory);

	BlackBoxSolverFactory *secondFactory;

	if(MultiGrid)
		secondFactory = createMultiGridSolverFactory( verboseNormFactory );
	else
		secondFactory = createPlainSolverFactory( verboseNormFactory );

	
	BlackBoxSolverFactory *solverFactory = new CombinedSolverFactory(
				nestedSolverFactory,		//BlackBoxSolverFactory *firstSolverFactory,
				secondFactory			//BlackBoxSolverFactory *secondSolverFactory 
				);

	solverFactory->addToDeleteList(nestedSolverFactory);
	solverFactory->addToDeleteList(secondFactory);

	StatisticsBlackBoxSolverWrapperFactory *wrapperFactory = new StatisticsBlackBoxSolverWrapperFactory(solverFactory);
	wrapperFactory->addToDeleteList(solverFactory);


	return wrapperFactory;

}










MultiGridInterface::MultiGridInterface(ParametersAdaptor3DRISM *params)
{
	m_params = params;

	m_inputGrid = NULL;
	m_outputGrid = NULL;
	m_solver = NULL;
	m_gamma = NULL;
	m_c = NULL;
	m_g = NULL;
	m_solutionFactory=NULL;

	
}


void MultiGridInterface::initInputGrid()
{
throw "Deprecated method MultiGridInterface::initInputGrid used!";

/*	m_inputGrid = new Grid3DRISM(
			m_params->getNx(),//Integer Nx,
			m_params->getNy(),//Integer Ny,
			m_params->getNz(),//Integer Nz,
			m_params->getDx(),//Real dRx,
			m_params->getDy(),//Real dRy,
			m_params->getDz()//Real dRz
			);*/
}

void MultiGridInterface::init()
{

	m_factories.init(m_params);

	m_solutionFactory = (SolutionFactory3DRISMR *)m_factories.m_solutionFactory;

	initOperations(&m_operations);
	//initInputGrid();
	

	GridDependentNormFactory *verboseNormFactory = createVerboseNormFactory();
	
	BlackBoxSolverFactory *subSolverFactory;
	if(m_params->useMultiGrid())
	{
		if(m_params->useNested())
			subSolverFactory = createNestedSolverFactory(verboseNormFactory,1);
		else
			subSolverFactory = createMultiGridSolverFactory(verboseNormFactory);
	}
	else
	{ 
		if(m_params->useNested())
			subSolverFactory = createNestedSolverFactory(verboseNormFactory,0);
		else
			subSolverFactory = createPlainSolverFactory(verboseNormFactory);

	}
	subSolverFactory->addToDeleteList(verboseNormFactory);

	GridIndependentInterface3DRISM *gridIndependent = 
			(GridIndependentInterface3DRISM *)m_factories.m_gridIndependent;
	MoleculeCoordinates *coors = gridIndependent->getSoluteCoordinates(); 


	ExtendGridNumeratorFactory *gridNumeratorFactory= new ExtendGridNumeratorFactory(	
				coors,			//MoleculeCoordinates *moleculeCoordinates,
				m_params->getBuffer(),	//Integer maxBuffer,
				m_params->getSpacing(),	//Real spacing,
				m_params->getNumberOfExtentions()+1, //+ m_params->getDepth(), //Integer Ngrids,
				m_params->getExtendFactor()	//Real bufferDecayFactor
			  );

	GridNumerator *gridNumerator = gridNumeratorFactory->createGridNumerator();

	ExtendGrid *extendGrid = new ExtendGrid(gridNumerator);
	extendGrid->addToDeleteList(gridNumerator);
	extendGrid->addToDeleteList(gridNumeratorFactory);


	ExtendSolution3DRISM *extendSolution = new ExtendSolution3DRISM();
	

	m_inputGrid = (Grid3DRISM *)gridNumerator->getGrid(0)->clone();
	

	m_solver = new ExtendSolver(
			m_inputGrid,  //Grid *initialGuessGrid,
			subSolverFactory, //BlackBoxSolverFactory *subSolverFactory,
			m_params->getNumberOfExtentions(),	//Integer numberOfExtentions,
			m_factories.m_solutionFactory,		//SolutionFactory *solutionFactory,
			extendSolution,		//BinaryOperation<Solution *> *extendSolution,
			extendGrid		//BinaryOperation<Grid *> *extendGrid
		);

	m_solver->addToDeleteList(subSolverFactory);

	m_solver->addToDeleteList(extendGrid);
	m_solver->addToDeleteList(extendSolution);
	
	m_outputGrid = (Grid3DRISM *)m_solver->getResultGrid()->clone();

	m_gamma = NULL;
	m_c = NULL;
	m_g = NULL;
	m_clong = NULL;
	m_minusBetaUshort = NULL;

}


MultiGridInterface::~MultiGridInterface()
{
	NULL_DELETE(m_inputGrid)
	NULL_DELETE(m_outputGrid)
	NULL_DELETE(m_solver)
	NULL_DELETE(m_gamma)
	NULL_DELETE(m_c)
	NULL_DELETE(m_g)
	NULL_DELETE(m_clong)
	NULL_DELETE(m_minusBetaUshort)
}

void MultiGridInterface::solve(Solution3DRISMR *initialGuess)
{

	m_gamma = (Solution3DRISMR*)m_solutionFactory->createSolution(m_outputGrid);
	
	m_solver->solve(initialGuess,m_gamma);

//	GridDependent3DRISM2 *gridDependent = (GridDependent3DRISM2 *)m_factories.createGridDependent(m_outputGrid);
	GridDependent3DRISM3 *gridDependent = (GridDependent3DRISM3 *)m_factories.createGridDependent(m_outputGrid);

	Closure3DRISM *closure = gridDependent->getClosure();

	NULL_DELETE(m_c);
	m_c = (Solution3DRISMR*)m_solutionFactory->createSolution(m_outputGrid);
	
	closure->calculateClosure(m_gamma,m_c);
	
	NULL_DELETE(m_g);	
	m_g = (Solution3DRISMR*)m_solutionFactory->createSolution(m_outputGrid);

	m_c->copy(m_g);
	addSolution3DRISMR(m_g,m_gamma);
	addScalarSolution3DRISMR(m_g,1);

	if(!m_minusBetaUshort)
	{	m_minusBetaUshort = gridDependent->getBetaUshort();
		m_minusBetaUshort->retain();
	}


	GridIndependent3DRISM3 *gridIndependent = (GridIndependent3DRISM3*)m_factories.m_gridIndependent;

	LongSiteSitePotential potLong(
			gridIndependent->getSoluteCharges(),	//MoleculeCharges *soluteCharges,
			gridIndependent->getSolventCharges(),	//MoleculeCharges *solventCharges,
			gridIndependent->getNgCoefficient(),			//Real erfCoefficient
			gridIndependent->getSigmaEpsilonTable(),
			gridIndependent->getLJCutoff()	
		);

	
	NULL_DELETE(m_clong);
	m_clong = (Solution3DRISMR *)m_solutionFactory->createSolution(m_outputGrid);

	buildPotential(
			gridIndependent->getSoluteCoordinates(),	//MoleculeCoordinates *soluteCoors,
			&potLong,					//SiteSitePotential *siteSitePotential,
			m_clong					//Solution3DRISMR *potential // output
		);
	
	mulScalarSolution3DRISMR(m_clong, -1.0/gridIndependent->getKBT() );
	
	
	NULL_DELETE(gridDependent);

}

void MultiGridInterface::solve()
{
	Solution3DRISMR *initialGuess = (Solution3DRISMR*)m_solutionFactory->createSolution(m_inputGrid);
	initialGuess->setZero();

	solve(initialGuess);

	NULL_DELETE(initialGuess);

}

void MultiGridInterface::getPrefix()
{
	char *dst;
	dst = strcpyUntil(m_prefix,m_params->getSoluteStructureFile(),".");
	dst = strcpyUntil(dst,"_in_","");
	dst = strcpyUntil(dst,m_params->getSolventDataFile(),".");
	dst = strcpyUntil(dst,"_","");
}

void MultiGridInterface::saveResults()
{
	getPrefix();
	saveResults3DRISM(
		getGamma(),	//Solution3DRISMR *gamma,
		getC(),	//Solution3DRISMR *c,
		getCLong(), // Solution3DRISMR *clong
		getG(),	//Solution3DRISMR *g,
		getMinusBetaUshort(), // Solution3DRISMR *minusBetaUshort
		m_prefix,	//const char *prefix,
		".3d"	//const char *suffix
	);
	Time dt = Statistics::getInstance()->getIterationTime();

	char str[256];
	sprintf(str,"%siterationTime.txt",m_prefix);
	FILE *f = fopen(str,"w");
	fprintf(f,"%lg\n",(double)dt);
	fclose(f);

//	char str[256];
	sprintf(str,"%sparameters.txt",m_prefix);
	f = fopen(str,"w");
//	fprintf(f,"%lg\n",(double)dt);
	fputs(m_params->getParameters()->toString(),f);	
	fclose(f);

	
}

void MultiGridInterface::saveFreeEnergies()
{
	getPrefix();

	GridIndependentInterface3DRISM *gridIndependent = 
		(GridIndependentInterface3DRISM *)m_factories.m_gridIndependent;

	GridDependentInterface3DRISM *gridDependent = 
		(GridDependentInterface3DRISM *)m_factories.createGridDependent(m_outputGrid);

	HNCFreeEnergy3DRISM *freeEnergy = new HNCFreeEnergy3DRISM(
				gridDependent->getClosure(),	//Closure3DRISM *closure,
			//	gridDependent->getBetaUlong(),	//Solution3DRISMK *betaUlongPotK,//-beta*longPot(K)
				(SolutionFactory3DRISMR *) m_factories.m_solutionFactory,	//SolutionFactory3DRISMR *solutionFactory,
				gridIndependent->getSiteDensities()->getDensity(),//Real *densities, //[Bohr^-3]
				gridIndependent->getSiteMultiplicities()->getSiteMultiplicities(),
				gridIndependent->getKBT()	//Real kBT//[Hartree]
			);

	Real freeEnergyValue = freeEnergy->calculateFreeEnergy(getGamma());

	freeEnergyValue = freeEnergyValue * Units::energyUnits()->unit2unit("Hartree",m_params->getOutputEnergyUnits());

	char fname[256];
	sprintf(fname,"%sHNC_FreeEnergy.txt",m_prefix);
	writeDoubleArrayToFile(fname,&freeEnergyValue,1);	

	NULL_DELETE(gridDependent);
	NULL_DELETE(freeEnergy);

}
