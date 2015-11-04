#include "readCoorFile.h"

#include "readPDBFile.h"
#include "readXYZFile.h"

#include <stdio.h>
#include <string.h>

void readCoorFile(	const char *file,
			std::list<AtomRecord> *records)
{
static char error[1024];
if(strstr(file,".pdb") || strstr(file,".PDB"))
{
	readPDBFile(file,records); 
}
else if(strstr(file,".xyz") || strstr(file,".XYZ") )
{
	readXYZFile(file,records);
}
else
{	sprintf(error,"readCoorFile: unknown file format of %s\n"
			" Only *.pdb and *.xyz files are supported",file);
	throw error;
}

}

