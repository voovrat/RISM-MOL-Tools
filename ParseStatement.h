#ifndef ParseStatement_h
#define ParseStatement_h

#include "Object.h"
class StringParser;

class ParseStatement : public Object
{
protected:

	char *m_errorPos;
	
//	ParseStatement *m_subExpected;
	char m_expected[1024];
	char m_name[256];	


public:

	ParseStatement(const char *name);

	virtual char *getName();
	char *getErrorPos();
	void getExpected(char *dst,Integer maxLen);

	void fillExpected(StringParser *sp,const char c);
	void fillExpected(StringParser *sp,const char *str,const char *prefix="expected");


	virtual Integer expectChar(StringParser *sp,char C);
	virtual Integer expectChars(StringParser *sp,const char *chars);
	virtual Integer expectRange(StringParser *sp,const char from,const char to);

	virtual Integer expectStatement(	StringParser *sp,
				    	ParseStatement *statement);


	virtual Integer parse(StringParser *sp)=0;

	virtual Integer isAlpha(const char c);
	virtual Integer isNumeric(const char c);
	virtual Integer isAlphaNumeric(const char c);


	virtual Integer operator()(StringParser *sp);

};



#endif
