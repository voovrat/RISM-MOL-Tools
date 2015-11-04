#include "assignForceField.h"

#include "AtomPattern.h"
#include "AtomPatternArray.h"
#include <list>
#include <string.h>

#include <stdio.h>

void assignForceField( 	AtomPatternArray *molecule,
			std::list<AtomPatternArray *> *forceField)
{
int atom,result;

for(atom=0;atom<molecule->m_N;atom++)
{
	AtomPattern *currentAtom = molecule->m_patternArray[atom];
	result = 0;

//	fprintf(stderr,"Atom#%d\n",atom);

	int patternNum=1;

	std::list<AtomPatternArray *>::iterator patternIterator;
	for(	patternIterator=forceField->begin();
		patternIterator!=forceField->end();
		patternIterator++)
	{
		AtomPatternArray *patternArray = *patternIterator;

	//	fprintf(stderr,"Pattern#%d (%s)\n",patternNum,patternArray->m_patternName);
		patternNum++;
		int subAtom;
		for(subAtom=0; subAtom<patternArray->m_N; subAtom++)
		{

		//	fprintf(stderr,"subAtom#%d\n",subAtom);
			AtomPattern *pattern = patternArray->m_patternArray[subAtom];
			
			if(pattern->m_forceFieldName[0] == 0 ) continue;

			if(currentAtom->match( pattern ))
			{	
				result = 1;
				strcpy( currentAtom->m_forceFieldName, 
					pattern->m_forceFieldName);
				break;
			}

		}//subAtom
		
		if(result) break;

	}//patternIterator

// i commented the next line because actually... 
// if no atoms matches, -> molecule[i].m_forceFieldName=="" and we can check this later...
// if(!result) throw "No atom matches ";


}//atom


}//function


