#include "Settings.h"

#include <list>
#include "AtomRecord.h"
#include "string.h"
#include "compareDistances.h"


void joinDistances(	std::list<AtomRecord> *atomlist,
			Real *distances,
			Integer Nsites,
			Integer *Joins
		)
{
std::list<AtomRecord>::iterator it1,it2;
int i,j;

Integer N2 = Nsites * Nsites;

memset(	Joins,	//void *s, 
	0,	// int c, 
	N2 * sizeof(Integer)	//size_t n
	);

for(i=0, it1 = atomlist->begin(); i<Nsites; i++,it1++)
{
	AtomRecord atom1 = *it1;
	for( j=i, it2=it1; j<Nsites; j++,it2++)
	{
		AtomRecord atom2 = *it2;
		if(	strcmp( atom1.element, atom2.element)==0  &&
			compareDistances(	distances,	//Real *distances,
						Nsites,	//Integer Nsites,
						i,	//Integer lineA,
						j	//Integer lineB,
						//Real eps = 1e-2 
					)	
		) //if
		{
			Joins[ i*Nsites + j ] = 1;
			Joins[ j*Nsites + i ] = 1;
		}
	}//for j

}//for i
}

/*
#include <stdio.h>
#include <stdlib.h>
#include "readCoorFile.h"
#include "calculateDistances.h"
#include "atomlist2coors.h"

main()
{

std::list<AtomRecord> atomlist;

readCoorFile(	"water.xyz",	//const char *file,
		&atomlist	//std::list<AtomRecord> *records
		);

Integer Nsites = atomlist.size();

Real *coors = (Real *)malloc( Nsites * 3 * sizeof(Real) );

atomlist2coors(	&atomlist,	//std::list<AtomRecord> *atomlist,
		coors		//Real *coors //Nsites * 3 real array
		);

Real *distances = (Real *)malloc( Nsites * Nsites * sizeof(Real) );

calculateDistances(	coors,	//Real *coors,
			Nsites,	//Integer Nsites,
			distances	//Real *distances,
			//Integer Dim =3
			);

Integer	*Joins = (Integer *)malloc( Nsites * Nsites * sizeof(Integer) );

 joinDistances(	&atomlist,	//std::list<AtomRecord> *atomlist,
		distances,	//Real *distances,
		Nsites,		//Integer Nsites,
		Joins		//Integer *Joins
	);

int i,j;
Integer *p = Joins;
for(i=0;i<Nsites;i++)
{
	for(j=0;j<Nsites;j++,p++)
	{
		printf("%ld\t",*p);
	
	}
	printf("\n");
}



free(coors);
free(distances);
free(Joins);


}
*/
