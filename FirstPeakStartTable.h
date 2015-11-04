#ifndef FirstPeakStartTable_h
#define FirstPeakStartTable_h

#include "Settings.h"

#include "Object.h"
#include "SiteSitePotential.h"

#include <stdlib.h>

class FirstPeakStartTable : public Object
{
protected:

 	Real *m_startPos;
	Real *m_maxPos;
	SiteSitePotential *m_ljPotential;

public:
	FirstPeakStartTable()  
	{
		m_startPos = NULL;
		m_maxPos = NULL;
	}

	void fill(	SiteSitePotential *ljPotential,
			Real beta,
			Real treshold = 1e-6,
			Real dr = 0.1,
			Real Rmax = 100
		);

	virtual ~FirstPeakStartTable()
	{
		if(m_startPos) free(m_startPos);
		m_startPos = NULL;

		if(m_maxPos) free(m_maxPos);
		m_maxPos = NULL;
	}

	Integer getNumSolventSites()
	{
		return m_ljPotential->getNumSolventSites();
	}

	Integer getNumSoluteSites()
	{
		return m_ljPotential->getNumSoluteSites();
	}


	Real getStartPos(Integer soluteSite,Integer solventSite)
	{
		return m_startPos[soluteSite * getNumSolventSites() + solventSite];
	}

	Real *getAllStartPos()
	{
		return m_startPos;
	}

	Real *getAllMaxPos()
	{
		return m_maxPos;
	}

	Real getMaxPos(Integer soluteSite, Integer solventSite)
	{
		return m_maxPos[soluteSite * getNumSolventSites() + solventSite];
	}

};

#endif
