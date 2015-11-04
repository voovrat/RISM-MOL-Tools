#ifndef SigmaEpsilonTable_h
#define SigmaEpsilonTable_h

#include "Object.h"

class MoleculeLJParameters;
class MixingRules;

class SigmaEpsilonTable : public Object
{
protected:

 	Real *m_sigma;
	Real *m_epsilon;

	Integer	m_numSoluteSites;
	Integer 	m_numSolventSites;

public:
	SigmaEpsilonTable(Integer numSoluteSites, Integer numSolventSites);

	void fill(MoleculeLJParameters *soluteParameters,
		  MoleculeLJParameters *solventParameters,
		  MixingRules *
		 // void (*mixingRules)(Real,Real,Real,Real,Real *,Real *)
		);

	virtual ~SigmaEpsilonTable();

	Integer getNumSolventSites()
	{
		return m_numSolventSites;
	}

	Integer getNumSoluteSites()
	{
		return m_numSoluteSites;
	}


	Real getSigma(Integer soluteSite,Integer solventSite)
	{
		return m_sigma[soluteSite * m_numSolventSites + solventSite];
	}

	Real *getAllSigma()
	{
		return m_sigma;
	}

	Real getEpsilon(Integer soluteSite,Integer solventSite)
	{
		return m_epsilon[soluteSite * m_numSolventSites + solventSite];	
	}

	Real *getAllEpsilon()
	{
		return m_epsilon;
	}	

};

#endif
