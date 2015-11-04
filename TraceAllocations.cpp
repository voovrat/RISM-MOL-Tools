#include "TraceAllocations.h"

#include "stacktrace.h"
#include "humanReadableNumber.h"

#include <string.h>
#include <stdio.h>

TraceAllocations::TraceAllocations(const char *className,const char *fname)
{	m_className = className;
	strcpy(m_logFname,fname);
	m_totalAllocated = 0;
	m_allocCount=0;

	fclose(fopen(fname,"w"));
	
}

Integer TraceAllocations::traceAlloc(Integer size,void *ptr)
{
static Integer allocID=0;

allocID++;

m_allocCount++;
m_totalAllocated=m_totalAllocated+size;

trace("ALLOC",size,allocID,ptr);
return allocID;
}

void TraceAllocations::traceDealloc(Integer size,void *ptr,Integer allocID)
{
m_allocCount--;
m_totalAllocated=m_totalAllocated-size;
trace("DEALLOC",size,allocID,ptr);


}

void TraceAllocations::trace(const char *prefix,Integer size,Integer id,void *ptr)
{
FILE *f = fopen(m_logFname,"r+");
if(!f) f=fopen(m_logFname,"w");
fseek(f,0,SEEK_END);

fprintf(f,"%s %d %p : %s : count = %d, size=%0.1lf%c (%+0.1lf%c)\n",
	prefix,
	(int)id,
	ptr,
	m_className,
	(int)m_allocCount,
	(double)human_readable_number(m_totalAllocated),human_readable_letter(m_totalAllocated),
	(double)human_readable_number(size),human_readable_letter(size)
	);

print_stacktrace(f//FILE *out = stderr, 
		 //unsigned Integer max_frames = 63
);

fclose(f);


}

