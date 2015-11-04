#ifndef ParseSolventComposition_h
#define ParseSolventComposition_h

#include "ParseSequence.h"
#include "ParseStatementFactory.h"
#include "ParseSolventComponent.h"

#include <list>
#include <string>

class ParseSolventComposition : public ParseSequence 
{
protected:
	SimpleParseStatementFactory<ParseSolventComponent> m_factory;
	std::list<std::string> *m_structureFiles;
	std::list<std::string> *m_forceFieldFiles;
	std::list<Real> *m_densities;

public:
	ParseSolventComposition(
		std::list<std::string> *structureFiles,
		std::list<std::string> *forceFieldFiles,
		std::list<Real> *densities
		)
	: ParseSequence(&m_factory)
	{
		m_structureFiles = structureFiles;
		m_forceFieldFiles = forceFieldFiles;
		m_densities = densities;
	}

//	virtual Integer parse( StringParser *sp); inherited

	virtual void elaborateStatement(ParseStatement *parseStatement)
	{

		ParseSolventComponent *parseSolventComponent = (ParseSolventComponent*)parseStatement;

		std::string structureFile = parseSolventComponent->m_solventFile;
		std::string forceFieldFile = parseSolventComponent->m_forceFieldFile;
		Real density = parseSolventComponent->m_density;

		m_structureFiles->push_back(structureFile);
		m_forceFieldFiles->push_back(forceFieldFile);
		m_densities->push_back(density);
	}

};

#endif
