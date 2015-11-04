#ifndef addIfUnique_h
#define addIfUnique_h

#include "hasElement.h"

#define addIfUnique(collection,element)  \
if(!hasElement( (collection).begin(), (collection).end(), element ) ) \
{	(collection).push_back(element); }

#endif
