#include "TextLog.h"

#include <stdio.h>


TextLog::TextLog()
{
	m_verboseLevel=100;
}

TextLog *TextLog::getInstance()
{
	static TextLog *instance = NULL;

	if(!instance) instance = new TextLog();

	return instance;
}

void TextLog::printString(Integer verbosity,
		 const char *S)
{
	if(m_verboseLevel < verbosity) return;

	fputs(S,stdout);
}

void TextLog::printDouble(Integer verbosity,
			  Real d)
{
	if(m_verboseLevel < verbosity) return;
	
	printf("%le",d);
}

void TextLog::printArrayH(Integer verbosity,
			Real *array,
			Integer length)
{
	if(m_verboseLevel < verbosity) return;

	Integer i;
	for(i=0;i<length;i++)
	{
		printf("%le\t",array[i]);
	}
	printf("\n");
}

void TextLog::printArrayV(Integer verbosity,
		 Real *array,
		 Integer length)
{
	if(m_verboseLevel < verbosity) return;

	Integer i;
	for(i=0;i<length;i++)
	{
		printf("%le\n",array[i]);
	}
}

void TextLog::printMatrix(Integer verbosity,
			 Matrix<Real> *matrix)
{
	if(m_verboseLevel < verbosity) return;

	Integer i,j;
	for(i=0;i<matrix->getNumRows();i++)
	{	for(j=0;j<matrix->getNumCols();j++)
		{
			printf("%le\t",matrix->getAt(i,j));
		}
		printf("\n");
	}				
}
