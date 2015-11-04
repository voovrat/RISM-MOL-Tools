#ifndef humanReadableNumber_h
#define humanReadableNumber_h


inline Real human_readable_number(Real x)
{
	return  (x>1000000000) ? (x/1000000000) : 	
		(x>1000000)	 ? (x/1000000) : 	
		(x>1000)	 ? (x/1000) : 	
		 x;
}

inline char human_readable_letter(Real x)
{
	return  (x>1000000000) ? 'G' : 	
		(x>1000000)	 ? 'M' : 	
		(x>1000)	 ? 'K' : 	
		 ' ';
}

#endif
