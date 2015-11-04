#ifndef Object_h
#define Object_h

#include <list>
#include <stdio.h>
#include "Settings.h"

#define DELETE(x)	\
if(x) 		\
{		\
(x)->release();	\
if((x)->isDeletable()) delete (x);	\
} 

#define NULL_DELETE(x) {DELETE(x) x=NULL;}

class Object
{
protected:
	std::list<Object*> deleteList;

	Integer m_retainCount;
public:
	Object()
	{
		m_retainCount = 1;
	}

	virtual void retain()
	{
		m_retainCount++;
	}

	virtual void release()
	{
		m_retainCount--;
	}

	Integer getRetainCount()
	{
		return m_retainCount;
	}

	virtual ~Object() 
	{
		cleanUpDeleteList();
	}

	Integer isDeletable()
	{
		return m_retainCount==0;
	}

	virtual void cleanUpDeleteList()
	{
		std::list<Object *>::iterator i;
		for(i=deleteList.begin(); i!=deleteList.end(); i++)
		{
			Object *obj = *i;
			NULL_DELETE(obj);
		}

		deleteList.clear();
	}

	void addToDeleteList(Object *obj)
	{
		deleteList.push_back(obj);
	}

	
};

#endif

