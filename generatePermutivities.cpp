#include "generatePermutivities.h"

#include <list>
#include <stdio.h>

// Generates permutivities of the list defined by Iterators begin/end
//template <class T,class Iterator>
#define generatePermutivitiesTemplate(T)\
void generatePermutivities(	std::list<T>  *items,\
				std::list< std::list<T> *> *permutivities /*out, should be empty on input*/\
			   )\
{\
if(items->size()==1){\
	std::list<T> *x = new std::list<T>;\
	*x = *items;\
	permutivities->push_back(x);\
	return;\
}\
\
std::list<T> subitems;\
std::list<T>::iterator it;\
std::list<std::list<T> *> subpermutivities;\
\
for(it=items->begin(); it!=items->end(); it++ )\
{\
	subitems = *items;\
	subitems.remove(*it);\
\
\
	generatePermutivities(	&subitems,\
				&subpermutivities );\
	std::list<std::list<T> *>::iterator subit;\
	for(subit = subpermutivities.begin(); subit!=subpermutivities.end(); subit++)\
	{\
		std::list<T> *x = new std::list<T>();\
		std::list<T> *sublist = *subit;\
\
		x->push_back(*it);\
		x->insert(x->end(),sublist->begin(),sublist->end());\
		delete sublist;\
		permutivities->push_back(x);\
	}\
	subpermutivities.clear();\
}\
}

generatePermutivitiesTemplate(int)
generatePermutivitiesTemplate(void *);

/*
main()
{
std::list<void *> A;

A.push_back((void *)"one");
A.push_back((void *)"two");
A.push_back((void *)"three");
A.push_back((void *)"four");

std::list<std::list<void*> *> permutA;

generatePermutivities( &A, &permutA);

std::list<std::list<void*> *>::iterator permuIt;
std::list<void*>::iterator it;

for(permuIt=permutA.begin(); permuIt!=permutA.end(); permuIt++)
{
	std::list<void*> *x = *permuIt;
	for(it=x->begin(); it!=x->end(); it++)
	{
		printf("%10s",(char *)*it);
	}
	printf("\n");
	delete x;

}


}
*/


