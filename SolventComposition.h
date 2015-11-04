#ifndef SolventComposition_h
#define SolventComposition_h

#include "Settings.h"
#include "Object.h"
#include <list>
#include <string>
#include "AtomRecord.h"

class SolventComposition : public Object
{
public:
	char m_path[256];

	std::list<std::string> m_structureFiles;
	std::list<std::string> m_forceFieldFiles;
	std::list<Real> m_densities;

	std::list<std::list<AtomRecord> *> m_atomListList;
	std::list<AtomRecord> m_bigAtomList;
	Real *m_bigDensities;


public:
	SolventComposition()
	{
		m_bigDensities = NULL;
	}

	virtual ~SolventComposition(); 
	

	void readComponentsFile(const char *file);
	void readStructureFiles();
	void mergeStructureFiles();
	void fillBigDensities();

	void init(const char *file)
	{
		readComponentsFile(file);
		readStructureFiles();
		mergeStructureFiles();
		fillBigDensities();
	}

	Integer getBigN()
	{
		if(m_bigAtomList.size()==0) mergeStructureFiles();
		return m_bigAtomList.size();
	}
	
	std::list<AtomRecord> *getBigAtomList()
	{
		if(m_bigAtomList.size()==0)
			mergeStructureFiles();

		return &m_bigAtomList;
	
	}

	std::list<std::list<AtomRecord> *> *getAtomListList()
	{
		return &m_atomListList;
	}

	Real *getBigDensities()
	{
		if(!m_bigDensities) fillBigDensities();
		return m_bigDensities;
	}	

};

#endif
