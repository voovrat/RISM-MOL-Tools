#include "GridIndex.h"

#include "Settings.h"

#include "Grid.h"
#include "GridDataFactory.h"
#include "ComparableGrid.h"
#include <stdio.h>

Object *GridIndex::findData(Grid *grid)
{

	ComparableGrid key (	grid,	//Grid *grid,
		    		m_gridComparator//compareGrids *comparator
			 );

	DATA_MAP_ITERATOR it = 	m_dataMap.find( &key );
	Object *data;

	if(it==m_dataMap.end())
	{
		Grid *gridClone0 = grid->clone();

		data = m_gridDataFactory->createData(gridClone0);

		data->addToDeleteList(gridClone0);

		Grid *gridClone = grid->clone();

		ComparableGrid *newKey = new ComparableGrid( gridClone,
							     m_gridComparator);

		m_dataMap[newKey] = data;
		
		newKey->addToDeleteList(gridClone);
		addToDeleteList(newKey);
		addToDeleteList(data);
#if DEBUG_LEAKS
	FILE *f=fopen("leaks.txt","r+");
	fseek(f,0,SEEK_END);
	fprintf(f,"GridIndex  this=%p : add to delete list %p  DeleteListSize=%d\n",this,data,(Integer)deleteList.size());
	fclose(f);
#endif	
		
	}
	else data = (*it).second;

	return data;
}

GridIndex::~GridIndex()
{

#if DEBUG_LEAKS
	FILE *f=fopen("leaks.txt","r+");
	fseek(f,0,SEEK_END);
	fprintf(f,"GridIndex this=%p cleanUpDeleteList Size=%d  [ ",this,(Integer)deleteList.size());

	std::list<Object *>::iterator i;
	for(i=deleteList.begin(); i!=deleteList.end(); i++)
	{
		Object *obj = *i;
		fprintf(f,"%p (%d)",obj,obj->getRetainCount());
	}

	fprintf(f,"\n");	

	fclose(f);
#endif	
//DATA_MAP_ITERATOR it;

//for(it=m_dataMap.begin();it!=m_dataMap.end();it++)
//{
// 	NULL_DELETE((*it).second )
//}

}
