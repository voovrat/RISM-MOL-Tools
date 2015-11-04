#ifndef SimpleMatrix_h
#define SimpleMatrix_h

#include "Matrix.h"

template<class T>
class SimpleMatrix : public Matrix<T>
{
protected:
	Integer m_M,m_N,m_allocatedRows,m_allocatedCols;
	T *m_data;
public:
	SimpleMatrix(	Integer numRows,
			Integer numCols,
			Integer allocedRows = 0,
			Integer allocatedCols = 0
		);


	virtual ~SimpleMatrix();


	T *getRawData()
	{
		return m_data;
	}

	virtual Integer getNumRows()
	{
		return m_M;
	}

	void setNumRows(Integer M)
	{
		m_M = M;
	}

	virtual Integer getNumCols() 
	{
		return m_N;
	}

	void setNumCols(Integer N)
	{
		m_N = N;
	}

	virtual T getAt(Integer row,Integer col)
	{
		return m_data[ row * m_allocatedCols + col ];
	}

	virtual void setAt(Integer row,Integer col,T x)
	{
		m_data[ row * m_allocatedCols + col ] = x;
	}


};


#endif
