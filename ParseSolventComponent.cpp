#include "ParseSolventComponent.h"

#include "StringParser.h"
#include "ParseSpaceString.h"
#include "ParseDouble.h"

Integer ParseSolventComponent::parse( StringParser *sp)
{
ParseSpaceString parseSpaceString;
ParseDouble parseDouble;

sp->skipChars(" \t");
if(!expectStatement(sp,&parseSpaceString)) return 0;

parseSpaceString.getString( m_solventFile,256);

sp->skipChars(" \t");

if(!expectStatement(sp,&parseSpaceString)) return 0;

parseSpaceString.getString(m_forceFieldFile,256);

sp->skipChars(" \t");
if(!expectStatement(sp,&parseDouble)) return 0;

m_density = parseDouble.getDouble();
return 1;

}

/*
#include <stdio.h>

main()
{
const char *str1="hello.xyz  hello.ff  33.36";
const char *str2="'hell o.xyz' 'hell o ff'  33.36";
StringParser sp1(str1);
StringParser sp2(str2);

ParseSolventComponent parseSolventComponent;

Integer R1=parseSolventComponent.parse(&sp1);

//char solvent[256],forcefield[256];
//Real density;

printf("R1=%ld : [%s] [%s] [%lg]\n ",R1,parseSolventComponent.m_solventFile,
			 parseSolventComponent.m_forceFieldFile,
			 parseSolventComponent.m_density);

Integer R2=parseSolventComponent.parse(&sp2);

//char solvent[256],forcefield[256];
//Real density;

printf("R2=%ld : [%s] [%s] [%lg]\n ",R2,parseSolventComponent.m_solventFile,
			 parseSolventComponent.m_forceFieldFile,
			 parseSolventComponent.m_density);


return 0;
}
*/
