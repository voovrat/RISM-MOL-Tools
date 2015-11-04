#include "JoinAndDistanceMatrices.h"

#include "SolventComposition.h"
#include <stdlib.h>

#include "buildBigDistances.h"
#include "joinDistances.h"
#include "removeJoined.h"
#include "numerateRDFs.h"

void JoinAndDistanceMatrices::uninit()
{

if(m_distances) free(m_distances);
m_distances = NULL;

if(m_joins) free(m_joins);
m_joins = NULL;

if(m_rdfNums) free(m_rdfNums);
m_rdfNums = NULL;

}

void JoinAndDistanceMatrices::init(SolventComposition *solventComposition)
{
uninit();

m_N = solventComposition->getBigN();
int BigN = m_N;
Integer BigN2 = BigN * BigN;

m_distances = (Real *)malloc( BigN2 * sizeof(Real) );
m_joins = (Integer *)malloc( BigN2 * sizeof(Integer) );
m_rdfNums = (Integer *)malloc( BigN2 * sizeof(Integer) );

buildBigDistances(	solventComposition->getAtomListList(),	//std::list<std::list<AtomRecord> *> *atomListList,
			BigN,	//Integer BigN, // total number of sites in all molecules
			m_distances	//Real *BigDistances // out, pre-allocated BigN*BigN*sizeof(Real)
			);

joinDistances(	solventComposition->getBigAtomList(),	//std::list<AtomRecord> *atomlist,
		m_distances,	//Real *distances,
		BigN,		//Integer Nsites,
		m_joins		//Integer *Joins
		);

removeJoined(	m_joins,	//Integer *Joins,
		BigN,	//Integer N,
		m_rdfNums	//Integer *RemovedJoins
		);

numerateRDFs(	m_rdfNums, BigN);

}



