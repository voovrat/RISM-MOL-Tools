#include "ParseAtomPattern.h"

#include <string.h>

#include "AtomPattern.h"
#include "AtomPatternArray.h"
#include "ParseStatementLine.h"

#include "ParseName.h"
#include "ParseAtom.h"
#include "StringParser.h"

#include "addIfUnique.h"

#include "ParseForceFieldName.h"
#include "ParseComment.h"

ParseAtomPattern::ParseAtomPattern()
: ParseStatement("atomPattern")
{
m_patternName[0]=0;
m_maxPattern = 0;
}

ParseAtomPattern::~ParseAtomPattern()
{
clearLines();
}

void ParseAtomPattern::clearLines()
{
std::list<ParseStatementLine *>::iterator it;

for(it=m_lines.begin(); it!=m_lines.end(); it++)
{
	NULL_DELETE(*it);
}

m_lines.clear();

std::list<ParseForceFieldName *>::iterator ffit;

for(ffit=m_forceFieldNames.begin(); ffit!=m_forceFieldNames.end(); ffit++)
{
	NULL_DELETE(*ffit);
}
m_forceFieldNames.clear();

}

void ParseAtomPattern::getPatternName(char *dst,int N)
{
	strncpy(dst,m_patternName,N);
}

Integer ParseAtomPattern::parse(StringParser *sp)
{
	ParseName parseName;
	ParseComment parseComment;
	SimpleParseStatementFactory<ParseAtom> parseAtomFactory;
//	ParseStatementLine parseLine(&parseAtomFactory);


	clearLines();
	m_maxPattern=0;

	if(!expectStatement(sp,&parseName)) return 0;

	parseName.getString(m_patternName,256);

	
	if(!expectChar(sp,':')) return 0;

	sp->skipChars(" \t");
	if(!sp->currentCharIs("\n")) return 0;
	sp->skipEOL();

	int result;

	do{

	if(expectStatement(sp,&parseComment)) continue;
	
	ParseStatementLine *parseLine = new ParseStatementLine(&parseAtomFactory);
	
	result = parseLine->parse(sp);

	if(!result || parseLine->getStatements()->size()==0)
	{
		NULL_DELETE(parseLine);
		break;
	}

	std::list<ParseStatement *>::iterator it;
	for(it=parseLine->getStatements()->begin(); it!=parseLine->getStatements()->end(); it++)
	{
		ParseAtom *parseAtom = (ParseAtom *)*it;
		if(parseAtom->getLabel() > m_maxPattern) 
				m_maxPattern = parseAtom->getLabel();
	}

	m_lines.push_back(parseLine);

	}while(1);

	do{
		sp->skipChars(" \t\n");

		if(expectStatement(sp,&parseComment)) continue;

		ParseForceFieldName *ffName = new ParseForceFieldName();
		
		if(!expectStatement(sp,ffName))
		{
			NULL_DELETE(ffName); break;
		}
	
		m_forceFieldNames.push_back(ffName);		

	}while(1);

	return 1;
}

void ParseAtomPattern::toAtomPatternArray( AtomPatternArray *atomPatternArray )
{
	std::list<ParseStatementLine *>::iterator lineIterator;
	std::list<ParseStatement *>::iterator atomIterator;

	atomPatternArray->alloc(m_maxPattern);
	AtomPattern **patterns = atomPatternArray->m_patternArray;	

	getPatternName(atomPatternArray->m_patternName,256);

	for(lineIterator = m_lines.begin(); lineIterator!=m_lines.end(); lineIterator++)
	{
		std::list<ParseStatement *> *statements = (*lineIterator)->getStatements();

		atomIterator= statements->begin();
		ParseAtom *firstParseAtom = (ParseAtom *)*atomIterator;

		AtomPattern *firstPattern = patterns[firstParseAtom->getLabel()-1];
		firstParseAtom->toAtomPattern(firstPattern);

		atomIterator++;

		for(; atomIterator!= (*lineIterator)->getStatements()->end(); atomIterator++)
		{
			ParseAtom *currentParseAtom = (ParseAtom *)*atomIterator;
			AtomPattern *currentPattern = patterns[currentParseAtom->getLabel()-1];
			
			currentParseAtom->toAtomPattern(currentPattern);

			
			addIfUnique(	 firstPattern->m_connectedTo, currentPattern );		
			addIfUnique(	currentPattern->m_connectedTo, firstPattern );

		}//atomIterator


	}//lineIterator

	
	std::list<ParseForceFieldName *>::iterator forceFieldIterator;
	for(	forceFieldIterator = m_forceFieldNames.begin();
		forceFieldIterator!=m_forceFieldNames.end();
		forceFieldIterator++ )
	{
		ParseForceFieldName *ffName = (ParseForceFieldName *)*forceFieldIterator;
		int id = ffName->m_parseAtom.getLabel()-1;
		strncpy(patterns[id]->m_forceFieldName,ffName->m_forceFieldName,256);		
	}
	
}
/*
main()
{

const char *str = "ethane:\n"
		 " C(1) H(2) H(3) H(4) C(5) \n"
		 " C(5) H(6) H(7) H(8) C(1) \n"
		 "\n"
		 "C(1) : methyl_C\n"
   		 "H(2) : methyl_H\n"
		 "C(5) : methyl_C\n"
		;

ParseAtomPattern parseAtomPattern;
StringParser sp(str);

int result = parseAtomPattern.parse(&sp);
int i;

if(result)
{
	int N = parseAtomPattern.getMaxPattern();

	printf("maxPattern: %d\n",N);

//	AtomPattern **patterns = new AtomPattern*[N];
//	std::vector<AtomPattern *> patterns(N);
	AtomPatternArray atomPatternArray;

//	for(i=0;i<N;i++)
//	{
//		patterns[i]= new AtomPattern();
//	}


	parseAtomPattern.toAtomPatternArray(&atomPatternArray);

	printf("pattern: %s\n",atomPatternArray.getPatternName());	

	AtomPattern **patterns = atomPatternArray.m_patternArray;

	for(i=0;i<N;i++)
	{
		printf("%d [%s] %s(%p):",i+1,patterns[i]->m_forceFieldName,patterns[i]->m_element,patterns[i]);
		std::list<AtomPattern *>::iterator it;
		for(	it=patterns[i]->m_connectedTo.begin();
	  		it!=patterns[i]->m_connectedTo.end();
			it++)
		{
			AtomPattern *x = *it;
			printf(" %s(%p)",x->m_element,x);
		}	
	printf("\n");


	}
}
else
{
	puts("PARSE ERROR");
}

}
*/
