#include "ParsePair.h"

#include <stdio.h>
#include <string.h>
//#include "ParseName.h"
//#include "ParseString.h"
//#include "ParseDouble.h"
//#include "StringParameter.h"
//#include "PlainDoubleParameter.h"
//#include "ParseDoubleWithUnits.h"
#include "StringParser.h"
#include "ParseValue.h"



Integer ParsePair::parse(StringParser *sp)
{
	ParseValue value(m_distanceUnits,m_energyUnits);

	sp->skipSpace();
	if(!expectChar(sp,'(')) return 0;

	sp->skipSpace();
	if(!expectStatement(sp,&value)) return 0;

	m_pair = new PairParameter();
	m_pair->setFirstPtr( value.retainValue() );
	m_pair->addToDeleteList( m_pair->getFirstPtr() );
	
	sp->skipSpace();
	if(!expectChar(sp,',')) return 0;

	sp->skipSpace();
	if(!expectStatement(sp,&value)) return 0;

	m_pair->setSecondPtr( value.retainValue() );
	m_pair->addToDeleteList( m_pair->getSecondPtr() );	

	sp->skipSpace();
	if(!expectChar(sp,')')) return 0;
	
	return 1;	
}
