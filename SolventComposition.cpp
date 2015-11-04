#include "SolventComposition.h"

#include "readFile.h"
#include "readCoorFile.h"
#include "ParseSolventComposition.h"
#include "StringParser.h"
#include <stdlib.h>
#include "AtomRecord.h"
#include <string.h>

SolventComposition::~SolventComposition()
{
std::list<std::list<AtomRecord> *>::iterator it;
for(it=m_atomListList.begin(); it!=m_atomListList.end(); it++)
	delete *it;

m_atomListList.clear();

if(m_bigDensities) free(m_bigDensities);
m_bigDensities = NULL;

}
	
void SolventComposition::readComponentsFile(const char *file)
{
char *str = readFile(file);
StringParser sp(str);

strcpy(m_path,file);
int N= strlen(file);
char *ptr = m_path + N;
while(N>0 && *ptr!='/') {N--;ptr--;}
if(*ptr=='/') *(ptr+1)=0;
else *ptr=0;

ParseSolventComposition parseSolventComposition(
	&m_structureFiles,//std::list<std::string> *structureFiles,
	&m_forceFieldFiles,//std::list<std::string> *forceFieldFiles,
	&m_densities	//std::list<Real> *densities
		);

parseSolventComposition.parse(&sp);
free(str);
}

void SolventComposition::readStructureFiles()
{
char fname[256];

std::list<std::string>::iterator it;

for(it=m_structureFiles.begin(); it!=m_structureFiles.end(); it++)
{
	std::list<AtomRecord> *atomlist = new std::list<AtomRecord>();
	sprintf(fname,"%s%s",m_path,(*it).c_str());
	readCoorFile(	fname,	//const char *file,
			atomlist	//std::list<AtomRecord> *records
			);
	m_atomListList.push_back(atomlist);
}

}

void SolventComposition::mergeStructureFiles()
{
std::list<std::list<AtomRecord> *>::iterator it;
for(it=m_atomListList.begin(); it!=m_atomListList.end(); it++)
{
	std::list<AtomRecord> *atomlist = *it;

	m_bigAtomList.insert( m_bigAtomList.end(), atomlist->begin(), atomlist->end() );

}

}

void SolventComposition::fillBigDensities()
{
Integer BigN = getBigN();

m_bigDensities = (Real *)malloc( BigN * sizeof(Real) );

std::list<Real>::iterator itDens;
std::list<std::list<AtomRecord> *>::iterator itStruct;

Real *pBigDens = m_bigDensities;
for( 	itDens = m_densities.begin(), itStruct = m_atomListList.begin();
	itDens != m_densities.end();
	itDens++, itStruct++)
{
	Integer N = (*itStruct)->size();
	while(N--)
	{
		*pBigDens = *itDens;
		pBigDens++;
	}
}

}

/*
main(int argc,char *argv[])
{
try{
SolventComposition solventComposition;

solventComposition.readComponentsFile(argv[1]);
solventComposition.readStructureFiles();
solventComposition.mergeStructureFiles()i;

printf("BigN:%ld\n",solventComposition.getBigN());

std::list<AtomRecord>::iterator it;
for(it=solventComposition.m_bigAtomList.begin(); 
    it!=solventComposition.m_bigAtomList.end();
    it++)
{
	AtomRecord atom = *it;
	printf("%s\t%lg\t%lg\t%lg\n",atom.element,atom.x,atom.y,atom.z);
}

} catch (const char *str)
{
puts(str);
}

return 0;
}
*/
