#include "SimpleMatrix.h"

#include <stdlib.h>
#include <string.h>

template<class T>
SimpleMatrix<T>::SimpleMatrix(	Integer M,
				Integer N,
				Integer allocatedRows,
				Integer allocatedCols)
{

	if(allocatedRows * allocatedCols == 0)
	{
		allocatedRows = M;
		allocatedCols = N;
	}

	m_allocatedRows = allocatedRows;
	m_allocatedCols = allocatedCols;
	
	m_M = M;
	m_N = N;

	m_data = (T *)malloc(m_allocatedRows * m_allocatedCols * sizeof(T) );
}	

template<class T>
SimpleMatrix<T>::~SimpleMatrix()
{
	if(m_data) free(m_data);
	m_data = NULL;
}

