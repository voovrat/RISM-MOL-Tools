#ifndef atomlist2coors_h
#define atomlist2coors_h

#include "Settings.h"
#include "AtomRecord.h"
#include <list>

inline void atomlist2coors(	std::list<AtomRecord> *atomlist,
				Real *coors //Nsites * 3 real array
			)
{
std::list<AtomRecord>::iterator it;
Real *XYZ = coors;
for( 	it=atomlist->begin(), XYZ=coors; 
	it != atomlist->end();
	it++, XYZ+=3 )
{
	XYZ[0] = (*it).x;
	XYZ[1] = (*it).y;
	XYZ[2] = (*it).z;
}

}


#endif
