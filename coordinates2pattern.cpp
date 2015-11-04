#include "coordinates2pattern.h"
#include "Settings.h"

#include "AtomRecord.h"
#include "AtomPattern.h"
#include "AtomPatternArray.h"

#include <list>
#include <string>
#include <map>
#include <string.h>

void coordinates2pattern(	std::list<AtomRecord> *records,
				AtomPatternArray *patternArray,
				std::map<std::string,Real> *sigmas)
{

patternArray->alloc(records->size());
AtomPattern **patterns = patternArray->m_patternArray;

std::list<AtomRecord>::iterator it1;
std::list<AtomRecord>::iterator it2;

Real sigma1,sigma2,sigma12;
Real dx,dy,dz;

for( it1 = records->begin(); it1 != records->end(); it1++)
{
	AtomRecord record1 = *it1;
	AtomPattern *pattern1 = patterns[record1.id-1];
	
	pattern1->m_label = record1.id;
	strcpy(pattern1->m_element,record1.element);
	
	sigma1 = (*(sigmas->find(record1.element))).second;

	for( it2 = records->begin(); it2 != records->end(); it2++)
	{
		AtomRecord record2 = *it2;
		if(record1.id == record2.id) continue;

		sigma2 = (*(sigmas->find(record2.element))).second;
		sigma12 = (sigma1 + sigma2)/2;
	
		dx = record1.x - record2.x;
		dy = record1.y - record2.y;
		dz = record1.z - record2.z;

		if( dx*dx + dy*dy + dz*dz < sigma12*sigma12 )
		{
			AtomPattern *pattern2 = patterns[record2.id-1];
			pattern1->m_connectedTo.push_back(pattern2);
		}//if	

	}//it2

}//it1

}//function

/*
#include "ParseAtomRadiusFile.h"
#include "readPDBFile.h"
#include "StringParser.h"
#include <stdlib.h>

#include "readFile.h"

main()
{
try{

char *radiiStr = readFile("sigmas.dat");
StringParser sp(radiiStr);

std::map<std::string,Real> sigmas;

ParseAtomRadiusFile parseSigmas(&sigmas);

parseSigmas.parse(&sp);

free(radiiStr);

std::list<AtomRecord> records;

const char *file = "benzene.pdb";

readPDBFile(file,&records);

AtomPatternArray molecule;

const char *ptr = strchr(file,'.');
int len = (ptr) ? ptr - file : strlen(file);

strncpy(molecule.m_patternName,file,len); 
molecule.m_patternName[len]=0;

coordinates2pattern(	&records, //std::list<AtomRecord> *records,
			&molecule, //AtomPatternArray *patternArray,
			&sigmas //std::map<std::string,Real> *sigmas
			);

std::string str;
molecule.toString(&str);


puts(str.c_str());


}catch(char *str)
{
printf("ERROR: %s\n",str);
}

}
*/
