#include "MGFactoryCollection3DRISM3.h"

#include "GridIndependent3DRISM3.h"
#include "Operator3DRISM2.h"

#include "Solution3DRISMR.h"
#include "ConditionSolver.h"
#include "DecayNormCondition.h"
#include "ScalProdNormSolution3DRISMR.h"

#include "AdjustableDampedIterationStep.h"
#include "AdaptiveDecayNormCondition.h"
#include "PtrDoubleParameter.h"
#include "PicardIterationStep.h"
#include "PLHNCClosure3DRISM.h"
#include "LorentzBerthelotRules.h"
#include "OPLSAARules.h"
#include "SiteMultiplicities.h"
#include "VerboseNorm.h"

#include "ParametersAdaptor3DRISM.h"
#include "DIISIterationStep.h"
#include "MDIISIterationStep.h"
#include "HNCClosure3DRISM.h"
#include "PLHNCClosure3DRISM.h"
#include "scalarProdSolution3DRISMR.h"

#include "HardSphereClosure3DRISM.h"
#include "GridIndependentInterface3DRISM.h"

GridIndependentData *MGFactoryCollection3DRISM3::createGridIndependent(ParametersAdaptor3DRISM *params)
{

GridIndependent3DRISM3 *gridIndependent=new GridIndependent3DRISM3();

m_gridIndependent = gridIndependent;

	gridIndependent->init(	params->getSoluteStructureFile(),	//const char *soluteFname,
				params->getSoluteDistanceUnits(),
				params->getSoluteEnergyUnits(),

				params->getSolventDataFile(),		//const char *solventFname,
				params->getSolventDistanceUnits(),
				params->getSolventEnergyUnits(),
				params->getSolventDensityDistanceUnits(),

				params->getSolventRDFsFile(),		//const char *solventRdfFname,
				params->getSolventRDFsUnits(),

				params->getSolventOmegaFile(),	//const char *omegaFname,
				params->getOmegaDistanceUnits(),			

				params->getKBT(),			//Real temperature,// Hartree
				params->getNgCoefficient(),		//Real ngCoeff,
				getMixingRules(params),			//void (*mixingRules)(Real,Real,Real,Real,Real*,Real*),
				getClosureFactory(params),	//ClosureFactory3DRISM *closureFactory
				params->useExponentBridge(),
				params->getExponentBridgeA(),
				params->getExponentBridgeC(),
				params->getExponentBridgeKmax(),
				params->getLJPotentialCutoff(),
				params->useLJCorrection()
		);

	return gridIndependent;
}

OperatorFactory * MGFactoryCollection3DRISM3::createOperatorFactory(ParametersAdaptor3DRISM *params)
{
	return new OperatorFactory3DRISM2();
}


DoubleParameter *MGFactoryCollection3DRISM3::createLambda(ParametersAdaptor3DRISM *params)
{
	m_lambdaValue = params->getLambda();
	return new PtrDoubleParameter(&m_lambdaValue);
}

IterationStepFactory *MGFactoryCollection3DRISM3::createFineGridIterationStepFactory(ParametersAdaptor3DRISM *params)
{

	IterationStepFactory *picardStepFactory = new PicardIterationStepFactory(addSolution3DRISMR);

	IterationStepFactory *fineGridStepFactory= new AdjustableDampedIterationStepFactory
			(	picardStepFactory,	//IterationStepFactory *subFactory, 
				addSolution3DRISMR,//void (*add)(Solution *,Solution *),
				subSolution3DRISMR,//void (*sub)(Solution *,Solution *),
				mulScalarSolution3DRISMR, 
						//void (*mulScalar)(Solution *,Real),
				getLambda(params),			//Real lambda,
				params->getDivergenceLambdaDecayFactor()//Real lambdaDecayFactor = 2
			);

	fineGridStepFactory->addToDeleteList(picardStepFactory);
	return fineGridStepFactory;
}

IterationStepFactory *MGFactoryCollection3DRISM3::createCoarseGridIterationStepFactory(ParametersAdaptor3DRISM *params)
{
	IterationStepFactory *subFactory;

	if(params->getIterationType() == ParametersAdaptor3DRISM::PICARD_ITERATION)
		subFactory = new PicardIterationStepFactory(addSolution3DRISMR);

	if(params->getIterationType() == ParametersAdaptor3DRISM::DIIS_ITERATION)
		subFactory = new  DIISIterationStepFactory(
			params->getNDIIS(),	//Integer NDIIS,
			&addSolution3DRISMR,	//void (*add)(Solution *,Solution *),
			&subSolution3DRISMR,	//void (*sub)(Solution *,Solution *),
			&mulScalarSolution3DRISMR,//void (*mulScalar)(Solution *,Real),
			&scalarProdSolution3DRISMR, //Real (*scalarProd)(Solution *,Solution *),
			getSolutionFactory(params)//SolutionFactory *solutionFactory,
		);

	if(params->getIterationType() == ParametersAdaptor3DRISM::MDIIS_ITERATION)
		subFactory = new  MDIISIterationStepFactory(
			params->getNDIIS(),	//Integer NDIIS,
			&addSolution3DRISMR,	//void (*add)(Solution *,Solution *),
			&subSolution3DRISMR,	//void (*sub)(Solution *,Solution *),
			&mulScalarSolution3DRISMR,//void (*mulScalar)(Solution *,Real),
			&scalarProdSolution3DRISMR, //Real (*scalarProd)(Solution *,Solution *),
			getSolutionFactory(params),//SolutionFactory *solutionFactory,
			DIIS_MAX_SKIP_COUNT,	//Integer maxSkipCount = DIIS_MAX_SKIP_COUNT,
			params->getDiisPreDamping(),//Real DIIS_damping = DIIS_DAMPING
			params->getDiisPostDamping()

		);




	IterationStepFactory *coarseGridStepFactory=new AdjustableDampedIterationStepFactory
			(	subFactory,	//IterationStepFactory *subFactory, 
				addSolution3DRISMR,//void (*add)(Solution *,Solution *),
				subSolution3DRISMR,//void (*sub)(Solution *,Solution *),
				mulScalarSolution3DRISMR, 
						//void (*mulScalar)(Solution *,Real),
				getLambda(params),			//Real lambda,
				params->getDivergenceLambdaDecayFactor()//Real lambdaDecayFactor = 2)
			);

	coarseGridStepFactory->addToDeleteList(subFactory);
	return coarseGridStepFactory;
}

SolverFactory *MGFactoryCollection3DRISM3::createCoarseGridSolverFactory(ParametersAdaptor3DRISM *params)
{
	GridDependentNormFactory *subNormFactory = new ScalProdNormSolution3DRISMRFactory();

	GridDependentNormFactory *normFactory = new VerboseNormFactory("coarse","\n",2,subNormFactory);
	normFactory->addToDeleteList(subNormFactory);	

	NormConditionFactory *normConditionFactory = 	new AdaptiveDecayNormConditionFactory(	
			normFactory,		//GridDependentNormFactory *normFactory
			getSolutionFactory(params),	//SolutionFactory *solutionFactory,
			params->getDecayFactor(),	//Real initialDecayFactor  = 10,
			params->getDecayFactorMultiplier(),//Real decayFactorMultiplier = 1.2,
			params->getDecayFactorDivider(),//Real decayFactorDivider = 2,
			params->getGrowFactor(),//Real growFactor =2,
			params->getMaxCoarseStepCount(),//Integer maxCount = 1000,
			params->getMinCoarseError(),//Real minError = 1e-13
			params->getMinDecayFactor(),//minDecayFactor = 1.1,
			params->getMaxDecayFactor(),//maxDecayFactor = 100
			params->getFirstGrowFactor()
	);
	
	normConditionFactory->addToDeleteList(normFactory);


	SolverFactory *coarseGridSolverFactory= new 	ConditionSolverFactory(	
				normConditionFactory, //Condition *condition,
				getSolutionFactory(params) //SolutionFactory *solutionFactory,
	);

	coarseGridSolverFactory->addToDeleteList(normConditionFactory);
	return coarseGridSolverFactory;
}

SolutionFactory *MGFactoryCollection3DRISM3::createSolutionFactory(ParametersAdaptor3DRISM *params)
{
	Integer numSites = ((GridIndependent3DRISM3 *)getGridIndependent(params))->getSiteMultiplicities()->getNumSites();
	SolutionFactory *solutionFactory=  new SolutionFactory3DRISMR(numSites);
	return solutionFactory;
}

ClosureFactory3DRISM 	*MGFactoryCollection3DRISM3::createClosureFactory(ParametersAdaptor3DRISM *params)
{
	ClosureFactory3DRISM *closureFactory;
	ClosureFactory3DRISM *xclosureFactory;

	if(params->getClosure()==ParametersAdaptor3DRISM::HNC_CLOSURE)
		closureFactory = new HNCClosureFactory3DRISM();
	
	if(params->getClosure()==ParametersAdaptor3DRISM::PLHNC_CLOSURE)	
		closureFactory = new PLHNCClosureFactory3DRISM();

//	if(params->getClosure()==ParametersAdaptor3DRISM::HARD_SPHERE_CLOSURE)
//		closureFactory = new HardSphereClosure3DRISM(params->getStringParameter("HardSphereRadiiFile"));	

	if(params->useHardCores()) 
	{
		xclosureFactory = new HardSphereClosureFactory3DRISM(
							params->getHardCoreRadiiFile(),
							params->getSoluteDistanceUnits(),
							closureFactory,
							(GridIndependentInterface3DRISM*)m_gridIndependent
							);

		xclosureFactory->addToDeleteList(closureFactory);
	}
	else 
		xclosureFactory = closureFactory;								 

	return xclosureFactory;
}

MixingRules 	*MGFactoryCollection3DRISM3::createMixingRules(ParametersAdaptor3DRISM *params)
{
	MixingRules *mixingRules;

	if(params->getMixingRules()==ParametersAdaptor3DRISM::LORENTZ_BERTHELOT_RULES)	
		mixingRules =  LorentzBerthelotRules::getInstance();

	if(params->getMixingRules()==ParametersAdaptor3DRISM::OPLSAA_RULES)
		mixingRules = OPLSAARules::getInstance();

	return mixingRules;
}

MGFactoryCollection3DRISM3::MGFactoryCollection3DRISM3()
{
	m_gridIndependent = NULL;
	m_operatorFactory = NULL;

	m_fineGridStepFactory = NULL;
	m_coarseGridStepFactory = NULL;
	m_coarseGridSolverFactory = NULL;
		
	m_solutionFactory = NULL;
	m_closureFactory = NULL;
	m_lambdaParameter = NULL;
	m_lambdaValue = 0;
	m_mixingRules = NULL;
}

void MGFactoryCollection3DRISM3::init(ParametersAdaptor3DRISM *params)
{
	m_gridIndependent = getGridIndependent(params);
	m_operatorFactory = getOperatorFactory(params);

	m_fineGridStepFactory = getFineGridIterationStepFactory(params);
	m_coarseGridStepFactory = getCoarseGridIterationStepFactory(params);
	m_coarseGridSolverFactory = getCoarseGridSolverFactory(params);
		
	m_solutionFactory = getSolutionFactory(params);
	m_closureFactory = getClosureFactory(params);
	m_lambdaParameter = getLambda(params);
	m_mixingRules = getMixingRules(params);
}

void MGFactoryCollection3DRISM3::uninit()
{
	NULL_DELETE(m_gridIndependent);
	NULL_DELETE(m_operatorFactory);

	NULL_DELETE(m_fineGridStepFactory);
	NULL_DELETE(m_coarseGridStepFactory);
	NULL_DELETE(m_coarseGridSolverFactory);
		
	NULL_DELETE(m_solutionFactory);
	NULL_DELETE(m_closureFactory);
	NULL_DELETE(m_lambdaParameter);
	m_lambdaValue = 0;
	m_mixingRules = NULL;
}
