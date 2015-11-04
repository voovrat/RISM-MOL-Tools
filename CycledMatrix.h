#ifndef CycledMatrix_h
#define CycledMatrix_h

#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"

template<class T>
class CycledMatrix : public Matrix<T>
{
protected:
	Integer m_allocatedRow,m_allocatedCol;
	Integer  m_filledRow,m_filledCol;
	Integer m_firstRow,m_firstCol;
	T *m_data;	

public:
	CycledMatrix(Integer allocatedRow,Integer allocatedCol)
	{
		m_allocatedRow = allocatedRow;
		m_allocatedCol = allocatedCol;


		m_data = (T *)malloc(m_allocatedRow * m_allocatedCol * sizeof(T) );		

		reset();

	}

	void reset()
	{
		m_filledRow = 0;
		m_filledCol = 0;

		m_firstRow = 0;
		m_firstCol = 0;
	}

	~CycledMatrix()
	{
		if(m_data) 	free(m_data);
		m_data = NULL;
	}


	virtual Integer getNumRows()
	{
		return m_filledRow;
	}

	virtual Integer getNumCols()
	{
		return m_filledCol;
	}

	virtual T getAt(Integer row,Integer col)
	{
		Integer i = (m_firstRow + row) % m_allocatedRow;
		Integer j = (m_firstCol + col) % m_allocatedCol;

		return m_data[ i * m_allocatedCol + j ];
	}

	virtual void setAt(Integer row,Integer col,T x)
	{
		Integer i = (m_firstRow + row) % m_allocatedRow;
		Integer j = (m_firstCol + col) % m_allocatedCol;

		m_data[ i * m_allocatedCol + j ] = x;	
	}

	void nextRow()
	{
		if(m_filledRow < m_allocatedRow)
		{
			m_filledRow++;
		}
		else
		{
			m_firstRow = (m_firstRow + 1) % m_allocatedRow;
		}
	}

	void nextCol()
	{
		if(m_filledCol < m_allocatedCol)
		{
			m_filledCol++;
		}
		else
		{
			m_firstCol = (m_firstCol + 1) % m_allocatedCol;
		}
	}

};

#endif
