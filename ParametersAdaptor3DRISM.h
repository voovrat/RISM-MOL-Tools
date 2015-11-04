#ifndef ParametersAdaptor3DRISM_h
#define ParametersAdaptor3DRISM_h

#include "ParametersAdaptor.h"


class ParametersAdaptor3DRISM : public ParametersAdaptor
{
public:
	enum {
		HNC_CLOSURE = 1,
		PLHNC_CLOSURE = 2
	};

	enum {
		LORENTZ_BERTHELOT_RULES =1 ,
		OPLSAA_RULES =2
	};

	enum {
		PICARD_ITERATION =1,
		DIIS_ITERATION =2,
		MDIIS_ITERATION = 3
	};

	enum {
		L2_NORM =1,
		HNC_NORM =2
	};

public:

	ParametersAdaptor3DRISM(Parameters *parameters)
	: ParametersAdaptor(parameters) {}

	virtual ~ParametersAdaptor3DRISM() {}

//#####  GRID

//# number of grid points on INITIAL fine grid in x,y,z directions.
GET_DOUBLE_PARAMETER("Nx",Nx) 
GET_DOUBLE_PARAMETER("Ny",Ny) 
GET_DOUBLE_PARAMETER("Nz",Nz)

//# grid sizes of initial grid in x,y,and z directions
GET_DOUBLE_PARAMETER("dx",Dx) //
GET_DOUBLE_PARAMETER("dy",Dy)  
GET_DOUBLE_PARAMETER("dz",Dz)


GET_DOUBLE_PARAMETER("Buffer",Buffer)
GET_DOUBLE_PARAMETER("Spacing",Spacing)


//#### ITERATION

//#iteration. valid values: 'Picard' or 'DIIS' (case sencentive)
BEGIN_CASE_PARAMETER("iteration",IterationType,Integer)
	CASE("Picard",PICARD_ITERATION)
	CASE("DIIS",DIIS_ITERATION)
	CASE("MDIIS",MDIIS_ITERATION)	
END_CASE_PARAMETER

//#Number of DIIS vectors (only usedm then iteration='DIIS')
GET_INT_PARAMETER("NDIIS",NDIIS);

//# Should we use multi grid? Valid values: 'yes' or 'no'
GET_BOOLEAN_PARAMETER("MultiGrid",useMultiGrid)

//#if yes, what is the multi grid depth?
//# (depth means, who much times the number of grid points will be fivided by two.
//# e.g. for the initial grid  128x128x128 with dx=dy=dz=0.1 [Angstr] and depth=2 
//# the coarse grid is 64x64x64 with dx=dy=dz=0.4 [Angstr]
GET_INT_PARAMETER("depth",Depth)

//# Number of extentions.
//# After the main cycle of iteration converge, the solutions will be prolongated 
//# to the larger grid, and iterations repeat.
//# this parameters regulates the number of extentions.
//# e.g. for initial grid 128x128x128 with dx=dy=dz=0.1[Angstr] and number of extentions =2
//#  the resultin grid is 512x512x512 with dx=dy=dz=0
GET_INT_PARAMETER("NumberOfExtentions",NumberOfExtentions)


// ExtendFactor
GET_DOUBLE_PARAMETER_WITH_DEFAULT("ExtendFactor",ExtendFactor,1.4)

//# Number Of pre smooting steps in multi-grid iteration
GET_DOUBLE_PARAMETER("NumberOfPreSmoothingSteps",NumberOfPreSmoothingSteps)

//#Number of post smoothing 
GET_DOUBLE_PARAMETER("NumberOfPostSmoothingSteps",NumberOfPostSmoothingSteps)

//#NumberOfMultiGridSubSteps. 1 - V iteration 2- W iteration
GET_DOUBLE_PARAMETER("NumberOfMultiGridSubSteps",NumberOfMultiGridSubSteps)

//# initial lambda coupling parameter 
GET_DOUBLE_PARAMETER("lambda",Lambda)

//# norm which is used to control convergence of the iterations
//# Valid values are: 'L2' and 'HNC'
BEGIN_CASE_PARAMETER("norm",NormType,Integer)
	CASE("L2",L2_NORM)
	CASE("HNC",HNC_NORM)
END_CASE_PARAMETER

//# decayFactor regulates, who often we calculate the norm.
//# let x[i] are the solutions, and n is the smallest natural, such, that
//# |x[n]-x[n+1]| < |x[0]-x[1]|/ DecayFactor
//# then the norm is calculated as |x[n]-x[0]|  
//# ( this allows to calculate norm more precicely, because |x[n]-x[0]| is a better 
//# approximation to |x*-x[0]|, than |x[n]-x[n+1]|
GET_DOUBLE_PARAMETER_WITH_DEFAULT("decayFactor",DecayFactor, 10)

//# if after fine-grid correction next coarse error is less than before correction, that means that not enough
//# steps was done ( error of grid correction is < than coarse error).
// The decay factor will be multiplied by DecayFactorMultiplier, and thus number of coarse iteration steps increase
GET_DOUBLE_PARAMETER("DecayFactorMultiplier",DecayFactorMultiplier)

//# if after fine-grid correction next coarse error is more than before correction, that means that too much
//# steps was done ( error of grid correction is > than coarse error).
//# The decay factor will be divided by DecayFactorMultiplier, and thus number of coarse iteration steps decrease
GET_DOUBLE_PARAMETER("DecayFactorDivider",DecayFactorDivider)

//#Minimal and maximal limits for decayFactor
GET_DOUBLE_PARAMETER("MinDecayFactor",MinDecayFactor)
GET_DOUBLE_PARAMETER("MaxDecayFactor",MaxDecayFactor)


//# tolerance which is used to stop the iterations.
//# iteratins stop, then norm (see decayFcator) is less than tolerance
//# value of tolrance depeds on the norm used and on the decay factor
GET_DOUBLE_PARAMETER("tolerance",Tolerance)

//###### DIVERGENCE

//#growFactor controls the condition to detect the divergence of iterations
//# when the norm of difference between sequential solutions grows more than 
//# by growFactor times, the iteration is supposed to diverge.
GET_DOUBLE_PARAMETER_WITH_DEFAULT("growFactor",GrowFactor, 2)

GET_DOUBLE_PARAMETER_WITH_DEFAULT("FirstGrowFactor",FirstGrowFactor,1);

//# divergenceLambdaDecayFactor. 
//# when the iteration diverge, the value of lambda is decreasing by divergenceLambdaDecayFactor, and iteration steps are continued with the new lambda
GET_DOUBLE_PARAMETER_WITH_DEFAULT("divergenceLambdaDecayFactor",DivergenceLambdaDecayFactor, 10)

//# Not more than MaxCoarseStepCount coarse grid steps is allowed on the coarse grid
GET_INT_PARAMETER("MaxCoarseStepCount",MaxCoarseStepCount)

//# If coarse grid norm reaches MinCoarseError, iteration steps stop
GET_DOUBLE_PARAMETER("MinCoarseError",MinCoarseError)


//######### SOLUTE

//# SoluteStructureFile describes the structure of the solute. 
//# it contain 6 columns (each line corresponds to one atom):
//# X,Y,Z,sigma,epsilon,charge
//# X,Y,Z are coordinates of atoms
//# sigma and epsilon are lennard-jones parameters
//# charge is a partial charge of atom
GET_STRING_PARAMETER("SoluteStructureFile",SoluteStructureFile)

//#Distance units, which are used in SoluteStructureFile for X,Y,Z and sigma
GET_STRING_PARAMETER("SoluteDistanceUnits",SoluteDistanceUnits)

//#Energy units, which are used in SoluteStructureFile for epsilon
GET_STRING_PARAMETER("SoluteEnergyUnits",SoluteEnergyUnits)

//######## SOLVENT

//# SolventDataFile describes the solvent atoms
//# it contains 4 columns (each line corresponds to one atom):
//# sigma, epsilon, charge, multiplicity
//# sigma and epsilon are Lennad-Jones parameters
//# charge is a partial charge of atom
//# multiplicity defines, how many identical sites are there in the solvent molecule
GET_STRING_PARAMETER("SolventDataFile",SolventDataFile)

//#Distance units, which are used in SolventDataFile for sigma
GET_STRING_PARAMETER("SolventDistanceUnits",SolventDistanceUnits)

//#Energy units, which are used in SolventDataFile for epsilon
GET_STRING_PARAMETER("SoventEnergyUnits",SolventEnergyUnits)

//#File, which contains bulk-solvent radial distribution functions 
//#Structure of file: 
//# 1st column - regular grid in R direction
//# next N * (N+1)/2 columns - samples of RDF functions
//# where N is number of unique solvent sites
//# order is g11 g12 ... g1N g22... g2N g33 ... gNN
//# where gIJ means RDF between I-th and J-th solvent sites
GET_STRING_PARAMETER("SolventRDFsFile",SolventRDFsFile)

//#Distance units, which are used for the first column in SolventRDFsFile
GET_STRING_PARAMETER("SolventRDFsUnits",SolventRDFsUnits)

//#File, which describes the omega functions of different sites
//# each line corresponds to one omega function
//# The file contain 3 columns: 
//# RDFnumber, omega_koefficient, omega_shift 
//# RDFnumber describes the number of RDF to which the omega function corresponds
//# where RDFs are numbered in the following order:
//# 0 - g11, 
//# 1 - g12,
//#  ...
//# N-1 - g1N
//#  N - g22
//# N+1 - g23
//# ...
//# 2N-2 - g2N
//# 2N-1 - g33
//# ...
//# N(N-1)/2 - gNN
//# 
//# where N is number of unique solvent sites,
//# gIJ means RDF between sites I and J
//#
//# the resulting omega function will be pre-multiplied by the omega_koefficient
//#
//# omega_shift defines the position of the delta sphere
//#
//# Thus, result is omega_koefficient*delta(|r-omega_shift|)
GET_STRING_PARAMETER("SolventOmegaFile",SolventOmegaFile)

//# Distance units used in the SolventOmegaFile
GET_STRING_PARAMETER("OmegaDistanceUnits",OmegaDistanceUnits);

//#units which are used in solventData file for density 
GET_STRING_PARAMETER("SolventDensityDistanceUnits",SolventDensityDistanceUnits)

//#Temperature of the solvent
GET_DOUBLE_PARAMETER("T",KBT) //NB: T is in energy units ths T -> KBT

//####### POTENTIALS AND CLOSURE

//# closure. Valid values are 'HNC' and 'KH'
//GET_STRING_PARAMETER("closure",Closure);
BEGIN_CASE_PARAMETER("closure",Closure,Integer)
	CASE("HNC",HNC_CLOSURE)
	CASE("KH",PLHNC_CLOSURE)
//	CASE("HardSphere",HARD_SPHERE_CLOSURE)
END_CASE_PARAMETER

//HardSpheres
//# Should we use hard cores? Valid values: 'yes' or 'no'
GET_BOOLEAN_PARAMETER("HardCores",useHardCores)

//HardCoreRadiiFile
//# File with the hard core radii
GET_STRING_PARAMETER("HardCoreRadiiFile",HardCoreRadiiFile);


//# mixing rules. Valid Values are 'LornentzBerthelot' and 'OPLSAA'
//# LorentzBerthelot means sigma12 = (sigma1+sigma2)/2, epsilon12=sqrt(epsilon1*epsilon2)
//#OPLSAA means sigma12=sqrt(sigma1*sigma2); epsilon12=sqrt(epsilon1*epsilon2);
BEGIN_CASE_PARAMETER("MixingRules",MixingRules, Integer)
	CASE("LorentzBerthelot",LORENTZ_BERTHELOT_RULES)
	CASE("OPLSAA",OPLSAA_RULES)
END_CASE_PARAMETER

//# Mixing coefficient for ng-procedure (multiplier of the argument of erf function ).
//# Determines, how smooth is the transition from the short-range to thelong-range function (the smaller - the smoother).
GET_DOUBLE_PARAMETER_WITH_DEFAULT("ngCoeff",NgCoefficient,0.5)

GET_STRING_PARAMETER("OutputEnergyUnits",OutputEnergyUnits);

// Exponential Bridge
GET_BOOLEAN_PARAMETER_WITH_DEFAULT("ExponentBridge",useExponentBridge,0)

GET_DOUBLE_PARAMETER_WITH_DEFAULT("ExponentBridgeA",ExponentBridgeA,1.5875)
GET_DOUBLE_PARAMETER_WITH_DEFAULT("ExponentBridgeC",ExponentBridgeC,1.1754)
GET_DOUBLE_PARAMETER_WITH_DEFAULT("ExponentBridgeKmax",ExponentBridgeKmax,0.7471);

GET_BOOLEAN_PARAMETER_WITH_DEFAULT("Nested",useNested,0)

GET_DOUBLE_PARAMETER_WITH_DEFAULT("NestedTolerance",NestedTolerance,0.1 * 0.0016 )  // 0.1 [kcal/mol]

GET_DOUBLE_PARAMETER_WITH_DEFAULT("NestedGrowFactor",NestedGrowFactor,2)
GET_DOUBLE_PARAMETER_WITH_DEFAULT("NestedMaxCoarseStepCount",NestedMaxCoarseStepCount,100)
GET_DOUBLE_PARAMETER_WITH_DEFAULT("NestedDecayFactor",NestedDecayFactor,5)

GET_DOUBLE_PARAMETER_WITH_DEFAULT("diisPreDamping",DiisPreDamping,0.3)
GET_DOUBLE_PARAMETER_WITH_DEFAULT("diisPostDamping",DiisPostDamping,0.3)

// Buffer Spacing 

GET_DOUBLE_PARAMETER_WITH_DEFAULT("LJPotentialCutoff",LJPotentialCutoff,0)
GET_BOOLEAN_PARAMETER_WITH_DEFAULT("LJCorrection",useLJCorrection,0)

	
};

#endif
