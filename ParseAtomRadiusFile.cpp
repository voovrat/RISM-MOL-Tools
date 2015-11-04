#include "ParseAtomRadiusFile.h"

#include "ParseAtomRadius.h"
#include "ParseSequence.h"

// add new elelent to m_sigmas map
// does not add a new statement to m_statements array
void ParseAtomRadiusFile::elaborateStatement(ParseStatement *parseStatement)
{
	ParseAtomRadius *parseAtomRadius = (ParseAtomRadius*)parseStatement;
	std::string key = parseAtomRadius->m_element;
	
	(*m_sigmas)[key] = parseAtomRadius->m_sigma;	
}
/*
#include <stdio.h>
#include "StringParser.h"

main()
{
const char *str= "# hello world\n" 
		" C : 10.7 \n"
		" H: 22.1 # hello \n"
		" N:15.33 #alilujjaaaa!\n";
StringParser sp(str);

std::map<std::string,Real> sigmas;

ParseAtomRadiusFile parseAtomRadiusFile(&sigmas);

parseAtomRadiusFile.parse(&sp);

std::map<std::string,Real>::iterator it;
for(it=sigmas.begin(); it!=sigmas.end(); it++)
{
	printf("%s : %lf \n",(*it).first.c_str(),(*it).second);

}


}
*/
