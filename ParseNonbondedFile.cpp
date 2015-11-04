#include "ParseNonbondedFile.h"

#include "ParseSigmaEpsilonCharge.h"

#include "Units.h"
#include "ParseComment.h"

Integer ParseNonbondedFile::parse(StringParser *sp)
{
ParseComment parseComment("[#;");
ParseSigmaEpsilonCharge parseSEC;

Units *DU = Units::distanceUnits();
Units *EU = Units::energyUnits();

int NParsed = 0;
do{
sp->skipChars(" \t\n");
if(sp->isOver()) return 1;

if(expectStatement(sp,&parseComment)) continue;

if(!expectStatement(sp,&parseSEC)) return NParsed>0;


SigmaEpsilonCharge sec;

sec.sigma = parseSEC.m_sigma * DU->unit2unit("nm","Angstr");
sec.epsilon = parseSEC.m_epsilon * EU->unit2unit("kJ/mol","kcal/mol");
sec.charge = parseSEC.m_charge;
	
(*m_ff)[parseSEC.m_atomType] = sec;
NParsed++;

}while(1);

}


/*
#include "readFile.h"
#include <stdio.h>

main()
{
try{
char *str = readFile("ffoplsaanb.itp");
StringParser sp(str);

std::map<std::string, SigmaEpsilonCharge> ff;

ParseNonbondedFile parseNonbondedFile(&ff);

parseNonbondedFile.parse(&sp);

std::map<std::string,SigmaEpsilonCharge>::iterator it;
for(it=ff.begin(); it!=ff.end(); it++)
{
SigmaEpsilonCharge sec = (*it).second;

printf("%s : %lf %lf %lf \n",(*it).first.c_str(),sec.sigma,sec.epsilon,sec.charge);

}


}catch(char *str)
{
puts(str);
}
}
*/
