#include "ParseDoubleTable.h"

#include "ParseLineOfDoubles.h"
#include "ParseComment.h"

#include <stdlib.h>
#include <list>

#include "Exception.h"


ParseDoubleTable::ParseDoubleTable() : ParseStatement("doubleTable")
{
	init();
}

void ParseDoubleTable::init()
{
	m_listlist = new std::list< std::list<double> *>();
	m_numberOfLines = 0;
	m_numberOfColumns = 0;
}


ParseDoubleTable::~ParseDoubleTable()
{
	uninit();
}

void ParseDoubleTable::uninit()
{
	
	if(m_listlist)
	{

		std::list<std::list<double>*>::iterator it;
	
		for(it=m_listlist->begin(); it!=m_listlist->end(); it++)
		{
			std::list<double> *l = *it;

			if(l) delete  l;
		}

	delete  m_listlist;
	}

	m_listlist=NULL;
	m_numberOfLines = 0;
	m_numberOfColumns = 0;
}

Real *ParseDoubleTable::createTable()
{
	Real *data = (Real *)malloc(m_numberOfLines * m_numberOfColumns * sizeof(Real));

	Integer i,j;

	std::list<std::list<double>*>::iterator it;

	
	Real *data_ptr= data;

	for(	i=0, it=m_listlist->begin();
		i<m_numberOfLines;
		i++, it++)
	{
		std::list<double> *l = *it;

		std::list<double>::iterator subit;
		for( 	j=0, subit = l->begin();
			j<m_numberOfColumns;
			j++, subit++, data_ptr++)
		{

			*data_ptr = *subit;
		}//for j
			
	}//for i

	return data;
}
	
Integer ParseDoubleTable::parse(StringParser *sp)
{
	ParseLineOfDoubles *parseLineOfDoubles;

	uninit();
	init();

	Integer ncol;

	m_numberOfLines = 0;
	m_numberOfColumns = 0;

	Integer lineInFile=0;		

	while(!sp->isOver())
	{
		std::list<double> *line = new std::list<double>();

		parseLineOfDoubles = new ParseLineOfDoubles(line);

		Integer R=parseLineOfDoubles->parse(sp);

		lineInFile++;
		ncol = line->size();

		if(ncol==0) 
		{ 	delete line; 
			continue;
		}

		if(!R)
		{
			delete line;
			break;
		}

		if(m_numberOfColumns && ncol != m_numberOfColumns)
		{
			char s[256];
			sprintf(s,"ParseDoubleTable: at line %ld: number of columns (%ld) differ from previous one (%ld)\n",lineInFile,ncol,m_numberOfColumns);
			throw new Exception(this,s);
		}
		
		m_numberOfColumns = ncol;

		m_listlist->push_back(line);
		m_numberOfLines++;
	}

	return 1;

}

