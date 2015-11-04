#include "SolutionRISM.h"

//#include "mex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Solution3DRISMOperation.h"

//#include "GridDependent1DRISMMatlab.h"

//#include "Params.h"
template<class T>
SolutionRISM<T>::SolutionRISM(	Grid *grid,
				Integer numberOfSites
			 	)
: Solution(grid)
{
//	if(!dynamic_cast<Grid3DRISM*>(grid))
//		throw "Solution3DRISMR: invalid type of Grid: should be Grid3DRISM";

	m_gamma = NULL;
	m_rawData = NULL;

	m_numberOfSites = numberOfSites;
//	m_siteMultiplicities = siteMultiplicities;

//	Grid3DRISM *g3d = (Grid3DRISM *)m_grid;
//	m_N=g3d->getNx() * g3d->getNy() * g3d->getNz();

}

template<class T>
SolutionRISM<T>::~SolutionRISM() 
{
	cleanUp();
}

template<class T>
void SolutionRISM<T>::setGamma(T **gamma)
{
	cleanUp();
	createGamma();

	memcpy(m_rawData,gamma[0], m_MN *sizeof(T));

}

template<class T>
T **SolutionRISM<T>::getGamma()
{
	return m_gamma;		
}

template<class T>
void SolutionRISM<T>::cleanUp()
{
	if(m_gamma)
	{
		free(m_gamma);
		free(m_rawData);

		m_gamma = NULL;
		m_rawData = NULL;
	}
}
    
// copy solution to the given destination.
// function does not allocate the memory. 
// result should be allocated before.    

template<class T>
void SolutionRISM<T>::copy(Solution *dst)
{
	SolutionRISM<T> *goodDst = dynamic_cast<SolutionRISM<T>*>(dst);

	if(!goodDst)
	{
		throw "SolutionRISM<T>::copy: invalid type of the destination object. Should be SolutionRISM<T>";
	}


	if( ! dst->getGrid()->isEqual(m_grid)
		|| m_numberOfSites != goodDst->getNumberOfSites() )
	{	
		throw "SolutionRISM<T>::copy : the solutions grids of source and destination should be of the same size";
		return;
	}

	if(!goodDst->getGamma())
		goodDst->setGamma(m_gamma);
	else
		{
		memcpy(goodDst->getRawData(),m_rawData, m_MN * sizeof(T) );
		}
}

template<class T>
void SolutionRISM<T>::createGamma()
{
	if(m_gamma) return;

	m_N = calculateGammaSize();
	m_MN = m_N * m_numberOfSites;

	m_rawData = (T *)malloc(m_MN * sizeof(T));

	m_gamma = (T **)malloc(m_numberOfSites * sizeof(T *));
	Integer i;
	for(i=0;i<m_numberOfSites;i++)
	{
		m_gamma[i] = m_rawData + m_N*i; //(Real *)malloc(N * sizeof(Real));
	}
}


	// returns the Zero solution on the grid "grid"
template<class T>
Solution *SolutionRISM<T>::setZero()
{
	memset(m_rawData,0,m_MN*sizeof(T));	
}







