#ifndef DecayNormCondition_h
#define DecayNormCondition_h

#include "RealNormCondition.h"

class Solution;
class SolutionFactory;
				
class DecayNormCondition : public RealNormCondition
{
protected:
//inherited
	//Solution *m_firstSolution;
	//Real m_firstError;
	//Real m_prevError;
	//Integer m_state;

	//Real m_tolerance;
	//Real m_errorOfTolerance; // in percents, how accurate should we estimate the tolerance
	//Norm *m_realNorm;
	//SolutionFactory *m_solutionFactory;

	//Integer m_n;		// number of iterations since restart
// until throwInteger the exception
	
		void saveError(const char *fname,Real error)
		{	
			FILE *f = fopen(fname,"r+");
			
			if(!f) 
				f=fopen(fname,"w");
			else
				fseek(f,0,SEEK_END);

			fprintf(f,"%e\n",error);	

			fclose(f);
		}


//inherited	
		virtual Integer stateInit(Solution *x,Solution *y,Real error)
		{
#ifdef SAVE_ERROR
			saveError("error.txt",error);
#endif
			return RealNormCondition::stateInit(x,y,error);
		}

//inherited	
		virtual Integer stateCheck(Solution *x,Solution *y,Real error)
		{
#ifdef SAVE_ERROR
			saveError("error.txt",error);
#endif
		  	return RealNormCondition::stateCheck(x,y,error);
		}
		virtual Integer checkRealError(Solution *x,Solution *y,Real error)
		{
			return 1;
		}

//inherited	
		virtual Integer stateDiverge(Solution *x,Solution *y,Real error)
		{
#ifdef SAVE_ERROR
			saveError("error.txt",error);
#endif
			return RealNormCondition::stateDiverge(x,y,error);
		}


public:
	DecayNormCondition(	Real decayFactor,
				Norm *norm,
				SolutionFactory *solutionFactory,
				Real growFactor =2,
				Integer maxCount = 1000,
				Real minError = 1e-13,
				Real firstGrowFactor = 1)
	: RealNormCondition(	0, 		//Real tolerance, 
				1/decayFactor, 	//Real errorOfTolerance,
				norm,		//Norm *fastNorm,
				NULL,		//Norm *realNorm,(will never invoked)
				solutionFactory,//SolutionFactory *solutionFactory,				
				growFactor	//Real growFactor
				,maxCount
				, minError
				, firstGrowFactor
			   )
	{
	}

//inherited	virtual ~RealNormCondition();

//inherited	virtual void restart();

//inherited	virtual Integer getNIterations()
	
//inherited	virtual Real getPrevError()

//inherited	virtual Integer check(Object *,Object *);

};

class DecayNormConditionFactory : public NormConditionFactory 
{
protected:
	Real m_decayFactor;
	SolutionFactory *m_solutionFactory;
	Real m_growFactor;
	Integer m_maxCount;
	Real m_minError;
	Real m_firstGrowFactor;

	virtual NormCondition *newNormCondition(Norm *norm)
	{
		return new DecayNormCondition(	
				m_decayFactor,	//Real decayFactor,
				norm,		//Norm *norm,
				m_solutionFactory,//SolutionFactory *solutionFactory,
				m_growFactor,	//Real growFactor =2,
				m_maxCount,//Integer maxCount = 1000,
				m_minError, //Real minError = 1e-13
				m_firstGrowFactor
			);
	}
public:
	DecayNormConditionFactory(GridDependentNormFactory *normFactory,
				Real decayFactor,
				SolutionFactory *solutionFactory,
				Real growFactor =2,
				Integer maxCount = 1000,
				Real minError = 1e-13,
				Real firstGrowFactor=1)
	: NormConditionFactory(normFactory)
	{
		m_firstGrowFactor = firstGrowFactor;
		m_decayFactor = decayFactor;
		m_solutionFactory = solutionFactory;
		m_growFactor = growFactor;
		m_maxCount = maxCount;
		m_minError = minError;
	}



};

#endif
