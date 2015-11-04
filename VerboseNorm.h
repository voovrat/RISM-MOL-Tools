#ifndef VerboseNorm_h
#define VerboseNorm_h

#include "Norm.h"
#include "GridDependentNormFactory.h"

class VerboseNorm : public Norm
{
protected:

	Norm *m_subNorm;
	const char *m_prefix;
	const char *m_suffix;
	Integer m_verbosity;

public:
	VerboseNorm(	const char *prefix,
			const char *suffix,
			Integer verbosity,
			Norm *subNorm)
	{
		m_subNorm = subNorm;
		m_prefix = prefix;
		m_suffix = suffix;
		m_verbosity = verbosity;
	}

	virtual Real calculateNorm(Object *x,Object *y);

};

class VerboseNormFactory : public GridDependentNormFactory
{
protected:
	const char *m_prefix;
	const char *m_suffix;
	Integer m_verbosity;
	GridDependentNormFactory *m_subNormFactory;
	
public:
	VerboseNormFactory(	const char *prefix,
				const char *suffix,
				Integer verbosity,
				GridDependentNormFactory *subNormFactory)
	{
		m_prefix = prefix;
		m_suffix = suffix;
		m_verbosity  = verbosity;
		m_subNormFactory = subNormFactory;
	}
	
	virtual Norm *createNorm(GridDependentData *gridDependent)
	{
		Norm *subNorm = m_subNormFactory->createNorm(gridDependent);
		Norm *norm = new VerboseNorm(
			m_prefix,	//const char *prefix,
			m_suffix,	//const char *suffix,
			m_verbosity,	//Integer verbosity,
			subNorm		//Norm *subNorm
		);

		norm->addToDeleteList(subNorm);
		return norm;
	}

};

#endif
