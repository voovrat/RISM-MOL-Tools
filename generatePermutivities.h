#ifndef generatePermutivities_h
#define generatePermutivities_h

#include <list>

// generate all possible permutivities (N!) of the elements in the list

void generatePermutivities(	std::list<int>  *items,
				std::list< std::list<int> *> *permutivities /*out, should be empty on input*/
			   );

void generatePermutivities(	std::list<void *>  *items,
				std::list< std::list<void *> *> *permutivities /*out, should be empty on input*/
			   );

#endif

