#include "ParseAtomPattern.h"
#include "sizeOfFile.h"
#include "ParseSequence.h"
#include "StringParser.h"
#include "ParsePatternFile.h"
#include "AtomPattern.h"
#include "AtomPatternArray.h"
#include "assignForceField.h"

#include "getPath.h"
#include "searchInPath.h"

#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "openOrDie.h"
#include "readFile.h"
/*
char error[1024];

FILE *openOrDie(const char *file,const char *prm="r")
{
FILE *f = fopen(file,prm);
if(!f) 
{
	sprintf(error,"cannot open %s\n",file);
	throw error;
}
return f;
}

char *readFile(const char *file)
{
FILE *f = openOrDie(file,"r");
int N = sizeOfFile(file);
char *str =(char *) malloc(N+1);
fread(str,N,1,f);
str[N]=0;
return str;
}
*/

#define MAX_FILE 1024

main(int argc,char *argv[])
{
char error[256];
try{

char inputFile[MAX_FILE];
char forceFieldFile[MAX_FILE];
char outputFile;

if(argc<=2)
{
puts("Usage: assignAtomTypes  input.pat  forceField.pat [ output.pat ] ");
puts("if output.pat is omitted - output to stdout");
return 1;
}

std::list<std::string> pathList;
getPath( getenv("PATH"), &pathList);

if(!searchInPath( argv[1], &pathList, inputFile, MAX_FILE ))
	throw "input pattern file not found";

if(!searchInPath( argv[2], &pathList, forceFieldFile, MAX_FILE ))
	throw "force Field file not found";



int N;

FILE *fout;

char *inputData;
char *forceFieldData;


inputData = readFile(inputFile);
forceFieldData = readFile(forceFieldFile);

if(argc>3)
	fout = openOrDie(argv[3],"w");
else
	fout = stdout;

StringParser inputsp(inputData);
StringParser ffsp(forceFieldData);


// read the forcefield
std::list<AtomPatternArray *> forceField;

ParsePatternFile parsePatternFile(&forceField);
parsePatternFile.parse(&ffsp);

free(forceFieldData);

//read the input molecule
ParseAtomPattern parseMolecule;
AtomPatternArray molecule;

parseMolecule.parse(&inputsp);

free(inputData);

parseMolecule.toAtomPatternArray(&molecule);

// assign the force field
assignForceField( 	&molecule,	//AtomPatternArray *molecule,
			&forceField	//std::list<AtomPatternArray *> *forceField
			);

// generate output 
int i;
for(i=0;i<molecule.m_N;i++)
{
if(molecule.m_patternArray[i]->m_forceFieldName[0]==0)
{
strcpy(molecule.m_patternArray[i]->m_forceFieldName,"UNKNOWN");
}

}

std::string outputStr;

molecule.toString(&outputStr);

fprintf(fout,"%s",outputStr.c_str());
fclose(fout);


std::list<AtomPatternArray *>::iterator patternIterator;
// delete forceField entries
for(patternIterator = forceField.begin(); patternIterator!=forceField.end(); patternIterator++)
{
	NULL_DELETE(*patternIterator);
}
}catch(const char *str)
{
printf("Exception: %s\n",str);
return 1;
}

return 0;
}
