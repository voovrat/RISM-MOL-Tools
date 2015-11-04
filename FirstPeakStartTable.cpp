#include "FirstPeakStartTable.h"

#include <math.h>

void FirstPeakStartTable::fill(
		SiteSitePotential *ljPotential,
		Real beta,
		Real treshold ,
		Real dr ,
		Real Rmax
	)
{
	m_ljPotential = ljPotential;

	Integer soluteSite,solventSite;

	Real r,startPos,maxPos;

	m_startPos = (Real *)malloc( getNumSoluteSites() * getNumSolventSites() * sizeof(Real) );
	m_maxPos = (Real *)malloc( getNumSoluteSites() * getNumSolventSites() * sizeof(Real) );
	
	for(soluteSite = 0; soluteSite < getNumSoluteSites(); soluteSite++)
	for(solventSite = 0; solventSite < getNumSolventSites(); solventSite++) 
	{
	//	Real startPos,maxPos;
	
		
	
		startPos =0;
		maxPos = 0;

		Real prev =0;

		for(r=0; r<Rmax; r+=dr)
  		{
			Real U = ljPotential-> calculatePotential(
						soluteSite,	//Integer soluteSite,
						solventSite,	//Integer solventSite,
						r		//Real R
						);

			Real expMinusBetaU = exp(-beta*U);

			if( expMinusBetaU > treshold && startPos==0) 
			{
				startPos = r;
			} 

			if( expMinusBetaU < prev )
			{
				maxPos = r-dr; 
				break; 
			}

			prev = expMinusBetaU;
		
		}

		m_startPos[soluteSite * getNumSolventSites() + solventSite ] = startPos;
		m_maxPos[soluteSite * getNumSolventSites() + solventSite ] = maxPos;
	}//solute + solvent

}

