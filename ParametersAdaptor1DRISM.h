#ifndef ParametersAdaptor1DRISM_h
#define ParametersAdaptor1DRISM_h

#include "ParametersAdaptor.h"
#include "Units.h"

#include "Matrix.h"
#include <map>
#include <string>

class ParametersAdaptor1DRISM : public ParametersAdaptor
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


   int m_nsites;
   Real *m_densities;
   Matrix<Real> *m_distMatrix;
   const char **m_siteNames;

   Real *m_sigma, *m_epsilon, *m_charge;

   std::map<std::string,Real> m_mol_dens_map;
   std::map<std::string,Integer> m_site_name_map;

   void fill_mol_dens_map();
   void read_sites();
   Real *read_site_data(const char *list_name);
   void read_distances();

public:

	ParametersAdaptor1DRISM(Parameters *parameters);

	void init();

	virtual ~ParametersAdaptor1DRISM(); 

//#####  GRID

GET_INT_PARAMETER_WITH_DEFAULT("N",N,4096);
GET_DOUBLE_PARAMETER_WITH_DEFAULT("dr",Dr,0.05);


Integer getNsites()
{
  return m_nsites;
}

Real *getDensities()
{
   return m_densities;
}

Matrix<Real> *getDistances()
{
   return m_distMatrix;
}

const char **getSiteNames()
{
   return m_siteNames;
}


Real *getSigma()
{
   return m_sigma;
}

Real *getEpsilon()
{
   return m_epsilon;
}

Real *getCharge()
{
   return m_charge;
}


GET_DOUBLE_PARAMETER_WITH_DEFAULT("temp",KBT, 298.15*Units::energyUnits()->unit2unit("K","Hartree"));

//# mixing rules. Valid Values are 'LornentzBerthelot' and 'OPLSAA'
//# LorentzBerthelot means sigma12 = (sigma1+sigma2)/2, epsilon12=sqrt(epsilon1*epsilon2)
//#OPLSAA means sigma12=sqrt(sigma1*sigma2); epsilon12=sqrt(epsilon1*epsilon2);
BEGIN_CASE_PARAMETER("MixingRules",MixingRules, Integer)
	CASE("LorentzBerthelot",LORENTZ_BERTHELOT_RULES)
	CASE("OPLSAA",OPLSAA_RULES)
END_CASE_PARAMETER


//# Mixing coefficient for ng-procedure (multiplier of the argument of erf function ).
//# Determines, how smooth is the transition from the short-range to thelong-range function (the smaller - the smoother).
//ngCoeff = 0.5 [Bohr^-1];
GET_DOUBLE_PARAMETER_WITH_DEFAULT("ngCoeff",NgCoefficient,0.5)


//# closure. Valid values are 'HNC' and 'KH'
//closure = 'HNC'; # again: let's try with HNC first, and do everything else afterwards
BEGIN_CASE_PARAMETER("closure",Closure,Integer)
	CASE("HNC",HNC_CLOSURE)
	CASE("KH",PLHNC_CLOSURE)
END_CASE_PARAMETER


GET_DOUBLE_PARAMETER_WITH_DEFAULT("lambda",Lamdba,0.5)

//# norm which is used to control convergence of the iterations
//# Valid values are: 'L2' and 'HNC'
BEGIN_CASE_PARAMETER("norm",NormType,Integer)
	CASE("L2",L2_NORM)
	CASE("HNC",HNC_NORM)
END_CASE_PARAMETER

GET_INT_PARAMETER_WITH_DEFAULT("MaxStep",MaxStep,10000);
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
GET_DOUBLE_PARAMETER_WITH_DEFAULT("tolerance",Tolerance,1e-12)

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


GET_BOOLEAN_PARAMETER_WITH_DEFAULT("Nested",useNested,0)

GET_DOUBLE_PARAMETER_WITH_DEFAULT("NestedTolerance",NestedTolerance,0.1 * 0.0016 )  // 0.1 [kcal/mol]

GET_DOUBLE_PARAMETER_WITH_DEFAULT("NestedGrowFactor",NestedGrowFactor,2)
GET_DOUBLE_PARAMETER_WITH_DEFAULT("NestedMaxCoarseStepCount",NestedMaxCoarseStepCount,100)
GET_DOUBLE_PARAMETER_WITH_DEFAULT("NestedDecayFactor",NestedDecayFactor,5)

GET_DOUBLE_PARAMETER_WITH_DEFAULT("diisPreDamping",DiisPreDamping,0.3)
GET_DOUBLE_PARAMETER_WITH_DEFAULT("diisPostDamping",DiisPostDamping,0.3)

	
};

#endif
