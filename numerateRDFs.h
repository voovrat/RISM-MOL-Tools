#ifndef numerateRDFs_h
#define numerateRDFs_h

// gives to rdfs the numbers 0,1,2, etc. and put them to removedJoins
// skip all -1 entries
// removedJoins could be obtained by using removeJoined

void numerateRDFs(	Integer *removedJoins, //in-out
			Integer BigN
		 );

#endif
