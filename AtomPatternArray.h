#ifndef AtomPatternArray_h
#define AtomPatternArray_h

#include "Object.h"
#include "Settings.h"

#include <vector>
#include <string>

class AtomPattern;

class AtomPatternArray : public Object
{
public:
	char m_patternName[256];
	AtomPattern **m_patternArray;
	Integer m_N;

	AtomPatternArray();
	virtual ~AtomPatternArray()
	{
		dealloc();
	}

	void setPatternName(const char *name);
	const char *getPatternName()
	{
		return m_patternName;
	}
	void getPatternName(char *dst,int N);

	void alloc(Integer N);
	void dealloc();

	void print();



	void toString(std::string *str);
};

#endif
