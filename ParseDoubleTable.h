#ifndef ParseDoubleTable_h
#define ParseDoubleTable_h

#include <list>

#include "Settings.h"

#include "ParseStatement.h"
#include "StringParser.h"

class ParseDoubleTable : public ParseStatement
{
protected:
	std::list<std::list<double> *> *m_listlist;
	Integer m_numberOfLines, m_numberOfColumns;

public:
	ParseDoubleTable();
	virtual ~ParseDoubleTable();

	void init();
	void uninit();

	virtual Real *createTable();
	
	virtual Integer getNumberOfLines()
	{
		return m_numberOfLines;
	}

	virtual Integer getNumberOfColumns()
	{
		return m_numberOfColumns;
	}

	virtual Integer parse(StringParser *sp);

};


#endif

