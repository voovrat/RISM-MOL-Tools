#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "openOrDie.h"
#include "readCoorFile.h"

#include "readFile.h"


#include "AtomRecord.h"
#include "SigmaEpsilonCharge.h"

#include <list>
#include <map>
#include <string>

#include "AtomPattern.h"
#include "AtomPatternArray.h"

#include "SigmaEpsilonCharge.h"

#include "StringParser.h"

#include "ParseAtomPattern.h"
#include "ParseNonbondedFile.h"
#include "ParseForceFieldFile.h"

#include "getPath.h"
#include "searchInPath.h"

#define MAX_FILE 1024

main(int argc,char *argv[])
{
static char error[1024];

try{
char coorsFile[MAX_FILE];
char patternFile[MAX_FILE];
const char *forceFieldFile0;
char forcefieldFile[MAX_FILE];

if(argc<=2)
{
puts("Usage:  ./createRismInput molecule_coors_file  moleculeWitAtomTypes.pat forcefield.itp output.rism" );
puts("molecule_coors_file in pdb or xyz format");
puts("moleculeWithAtomTypes.pat should be obtained from molecule_coors_file "
     "by using ./coors2pat and ./assignAtomTypes"
);
puts("forcefiled.itp - nonbonded part of gromacs forcefield file. Also can be *.ff file (where both: pattern and nonbonded parts are stored)");
puts("output.rism - output rism file ");
puts(" if output.rism is omitted - output to stdout");
puts(" if forcefield.itp is omitted ffoplsaanb.itp is used");
return 1;
}

std::list<std::string> pathList;

getPath( getenv("PATH"), &pathList );


if(!searchInPath(argv[1],&pathList,coorsFile,MAX_FILE))
	throw "coors file not found";
if(!searchInPath(argv[2],&pathList,patternFile,MAX_FILE))
	throw "pattern file not found";

//patternFile = argv[2];

if(argc>3)
	forceFieldFile0 = argv[3];
else 
	forceFieldFile0 = "ffoplsaanb.itp";

if(!searchInPath(forceFieldFile0,&pathList,forcefieldFile,MAX_FILE))
	throw "gromacs force field itp file not found";


FILE *fout;
if(argc>4)
	fout = openOrDie(argv[4],"w");
else
	fout = stdout;

//  read coors
std::list<AtomRecord> coors;
readCoorFile(coorsFile,&coors);

// read molecule pattern with assigned types
AtomPatternArray molPattern;

char *patternStr = readFile(patternFile);
StringParser patsp(patternStr);

ParseAtomPattern parseAtomPattern;
parseAtomPattern.parse(&patsp);
parseAtomPattern.toAtomPatternArray(&molPattern);

free(patternStr);

// read gromacs itp forcefiled file
std::map<std::string,SigmaEpsilonCharge> forcefield;

char *ffStr = readFile(forcefieldFile);
StringParser ffsp(ffStr);

std::list<AtomPatternArray *> patterns;
std::list<AtomPatternArray *>::iterator itKills;

ParseNonbondedFile parseItp(&forcefield);
ParseForceFieldFile parseFF(&forcefield,&patterns);

if(!parseItp.parse(&ffsp) && !parseFF.parse(&ffsp)) 
	throw "cannot parse force field file";

for(itKills=patterns.begin();itKills!=patterns.end();itKills++) delete *itKills;
patterns.clear();

free(ffStr);

// read atom coordinates, find appropriate force field values and print everything
std::list<AtomRecord>::iterator it;
for(it=coors.begin(); it!=coors.end(); it++)
{
	AtomRecord rec = *it;
	if(rec.id<1 || rec.id>molPattern.m_N) 
		throw "inconsistent coordinates and pattern files";

	AtomPattern *pat = molPattern.m_patternArray[rec.id-1];

	std::map<std::string,SigmaEpsilonCharge>::iterator mapit;
	mapit = forcefield.find(pat->m_forceFieldName);

	if(mapit == forcefield.end())
	{
		sprintf(error,"No atomtype `%s' in itp file %s\n",
				pat->m_forceFieldName, forcefieldFile);
		throw error;
	}

	SigmaEpsilonCharge sec = (*mapit).second;

	fprintf(fout,"%10.5lf%10.5lf%10.5lf%10.5lf%10.5lf%10.5lf\n",
			rec.x, rec.y, rec.z,  sec.sigma, sec.epsilon, sec.charge);
}

}catch(const char *str)
{
printf("ERROR : %s\n",str);
}


return 0;
}
