#ifndef TraceAllocations_h
#define TraceAllocations_h


class TraceAllocations
{
protected:
	void trace(const char *prefix,Integer size,Integer id,void *ptr);

public:

	Integer m_allocCount;
	Integer m_totalAllocated;
	char m_logFname[256];	
	const char *m_className;

 	TraceAllocations(const char *className,
			const char *fname);



	Integer  traceAlloc(Integer size,void *ptr);
	void traceDealloc(Integer size,void *ptr,Integer allocID=0);

};


#endif
