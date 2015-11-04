#include "calculateLineAndCol.h"
#include "Settings.h"


void calculateLineAndCol(	const char *text,
			 	const char *pos,
				Integer *line, //out
				Integer *col   //out
			)
{
	const char *ptr;
	
	*line=1;
	*col=1;
	for(ptr=text;ptr<pos;ptr++)
	{
		(*col)++;
		if(*ptr=='\n') 
		{
			(*line)++;
			*col=1;
		}
	}

}

