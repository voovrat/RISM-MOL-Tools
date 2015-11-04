#ifndef JoinAndDistanceMatrices_h
#define JoinAndDistanceMatrices_h

#include "Settings.h"
#include "Object.h"
#include <stdio.h>

class SolventComposition;

// Class to fill and store matrices with distances and joins
class JoinAndDistanceMatrices : public Object
{
public:
	Real *m_distances;
	Integer *m_joins;
	Integer *m_rdfNums;
	Integer m_N;

public:
	JoinAndDistanceMatrices()
	{
		m_distances = NULL;
		m_joins = NULL;
		m_rdfNums = NULL;
		m_N = 0;
	}
	
	virtual ~JoinAndDistanceMatrices() { uninit();}

	void init(SolventComposition *solventComposition);
	void uninit();

	Real *getDistances()
	{
		return m_distances;
	}

	Integer *getJoins()
	{
		return m_joins;
	}

	Integer *getRdfNums()
	{
		return m_rdfNums;
	}

	Integer getN()
	{
		return m_N;
	}
};


#endif
