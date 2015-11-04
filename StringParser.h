#ifndef StringParser_h
#define StringParser_h

#include "Object.h"

class StringParser : public Object
{
protected:
	const char *m_ptr;
	Integer m_error;	



public:
	
	StringParser(const char *string);


	static Integer isCharInString(char c,const char *char_set);
	
	Integer currentCharIs(const char *char_set)
	{
		return isCharInString(*m_ptr,char_set);
	}


	Integer getError()
	{
		return m_error;
	}

	char getCurrentChar()
	{
		return *m_ptr;
	}

	const char *getPtr()
	{
		return m_ptr;
	}
	
	void setPtr(const char *ptr)
	{
		m_ptr = ptr;
	}

	Integer isOver()
	{
		return !*m_ptr;
	}

	void skipChars(const char *chars);	
	void skipSpace();
	void skipEOL(); 
	void skipUntil(const char *delim);

	Real 	getDouble();
	Integer 	getInt();
	char	getChar();

	void 	getUntil(const char *delim,char *str,Integer maxChar);
	void 	getWord(char *word,Integer maxChar);
	void 	getLine(char *line,Integer maxChar);
	
};

#endif
