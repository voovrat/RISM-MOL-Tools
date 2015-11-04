#ifndef TextLog_h
#define TextLog_h

#include "Object.h"
#include "Matrix.h"

class TextLog : public Object
{
protected:
	Integer m_verboseLevel;	

	TextLog();

public:
	static TextLog *getInstance();

	void setVerboseLevel(Integer level)
	{
		m_verboseLevel = level;
	}

	Integer getVerboseLevel()
	{
		return m_verboseLevel;
	}

	virtual void printString(Integer verbosity,
				 const char *S);

	virtual void printDouble(Integer verbosity,
				Real d);

	virtual void printArrayH(Integer verbosity,
				Real *array,
				Integer length);

	virtual void printArrayV(Integer verbosity,
				 Real *array,
				 Integer length);

	virtual void printMatrix(Integer verbosity,
				 Matrix<Real> *matrix);
				
};


#endif
