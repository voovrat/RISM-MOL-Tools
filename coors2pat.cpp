#include "ParseAtomRadiusFile.h"
#include "readPDBFile.h"
#include "readXYZFile.h"
#include "StringParser.h"
#include "readFile.h"
#include "coordinates2pattern.h"
#include "openOrDie.h"
#include "AtomPatternArray.h"

#include "getPath.h"
#include "searchInPath.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <map>
#include <list>

#define MAX_STRING 1024

main(int argc,const char *argv[])
{
try{

std::list<std::string> pathList;

 const char *sigmaFile0;
 char sigmaFile[MAX_STRING];
 char moleculeFile[MAX_STRING];

FILE *fout;

if(argc<=1)
{
	puts("Usage:  coors2pat molecule_file sigmas.dat output.pat ");
	puts("if output.pat is omitted - output to stdout");
	puts("if sigmas.dat is omitted - 'sigmas.dat' file is default");
	puts("molecule_file - in xyz or pdb format");
	return 1;
}

getPath(getenv("PATH"),	//const char *pathstr, 
	&pathList	//std::list<std::string> *pathList
	);

//char fullName[256];
if(! searchInPath(	argv[1],	//const char *fname,
		 	&pathList,	//std::list<std::string> *pathList,
			moleculeFile,	//char *fullName,
			MAX_STRING		//int maxN
		 ) )
throw "molecule_file could not be opened";

//moleculeFile = argv[1];

if(argc<=2) // 0 + 1
{
  sigmaFile0 = "sigmas.dat";
}
else
  sigmaFile0 = argv[2];

if(! searchInPath(	sigmaFile0,	//const char *fname,
		 	&pathList,	//std::list<std::string> *pathList,
			sigmaFile,	//char *fullName,
			MAX_STRING		//int maxN
		 ) )
throw "simgas_file could not be opened";

if(argc<=3) 
{
	fout = stdout;
}
else
{
	fout = openOrDie(argv[3],"w");
}


char *radiiStr = readFile(sigmaFile);
StringParser sp(radiiStr);

std::map<std::string,Real> sigmas;

ParseAtomRadiusFile parseSigmas(&sigmas);

parseSigmas.parse(&sp);

free(radiiStr);

std::list<AtomRecord> records;

if(strstr(moleculeFile,".pdb"))
{
	readPDBFile(moleculeFile,&records); 
}
else if(strstr(moleculeFile,"xyz"))
{
	readXYZFile(moleculeFile,&records);
}
else
{
	throw "unknown file format. Only PDB and XYZ are supported";
}


AtomPatternArray molecule;

const char *ptr = strchr(moleculeFile,'.');
//int len =  ptr - moleculeFile;

const char *ptr0 = ptr;
while(ptr0>=moleculeFile && *ptr0!='/') ptr0--;
ptr0++;

int len = ptr-ptr0;

strncpy(molecule.m_patternName,ptr0,len); 
molecule.m_patternName[len]=0;

coordinates2pattern(	&records, //std::list<AtomRecord> *records,
			&molecule, //AtomPatternArray *patternArray,
			&sigmas //std::map<std::string,Real> *sigmas
			);

std::string str;
molecule.toString(&str);


fputs(str.c_str(),fout);
fclose(fout);

}catch(const char *str)
{
printf("ERROR: %s\n",str);
}

}

