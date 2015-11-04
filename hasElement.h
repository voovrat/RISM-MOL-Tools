#ifndef hasElement_h
#define hasElement_h

// add element to the collection if this collection does not have one (which is "==" to that element )

template< class Iterator, class T>
inline int hasElement( Iterator begin, Iterator end, T object)
{
Iterator it;
for(it=begin; it!=end; it++)
{
	if(*it == object) return 1;
}
return 0;
}


#endif
