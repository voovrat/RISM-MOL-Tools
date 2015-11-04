#include "SigmaEpsilonTable.h"

#include <stdlib.h>

#include "MoleculeLJParameters.h"
#include "MixingRules.h"

SigmaEpsilonTable::SigmaEpsilonTable(Integer numSoluteSites, Integer numSolventSites)
{

	m_numSoluteSites = numSoluteSites;
	m_numSolventSites = numSolventSites;

	Integer N = numSoluteSites * numSolventSites;

	m_sigma = (Real *)malloc( N * sizeof(Real) );
	m_epsilon = (Real *)malloc( N * sizeof(Real) );

}

SigmaEpsilonTable::~SigmaEpsilonTable()
{
	free(m_sigma);
	free(m_epsilon);
	m_sigma =  m_epsilon = NULL;
}


void SigmaEpsilonTable::fill(
		  MoleculeLJParameters *soluteParameters,
		  MoleculeLJParameters *solventParameters,
		 // void (*mixingRules)(Real,Real,Real,Real,Real *,Real *)
		MixingRules *mixingRules
		)
{
Integer i,j;

Real *sigma12,*epsilon12 ;

sigma12 = m_sigma;
epsilon12 = m_epsilon;

Real sigma1,epsilon1,sigma2,epsilon2;

for(i=0;i<m_numSoluteSites;i++)
{
	sigma1 = soluteParameters->getSigma()[i];
	epsilon1 = soluteParameters->getEpsilon()[i];

	for(j=0;j<m_numSolventSites;j++, sigma12++, epsilon12++)
	{
		sigma2 = solventParameters->getSigma()[j];
		epsilon2 = solventParameters->getEpsilon()[j];


		(*mixingRules)(	sigma1,
				epsilon1, 
				sigma2,
				epsilon2,
				sigma12,
				epsilon12
			);
	}
}

}



