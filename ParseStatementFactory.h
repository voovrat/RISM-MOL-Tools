#ifndef ParseStatementFactory_h
#define ParseStatementFactory_h


class ParseStatementFactory : public Object
{
public: 
	virtual ParseStatement *createParseStatement()=0;
};

template<class T>
class SimpleParseStatementFactory : public ParseStatementFactory
{
public:
	virtual ParseStatement *createParseStatement()
	{
		return new T();
	}
};

#endif
