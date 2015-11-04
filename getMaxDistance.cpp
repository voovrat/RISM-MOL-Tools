#include "getMaxDistance.h"

#include "Settings.h"
#include <math.h>

Real getMaxDistance(	Real *coors,	//N*3
			Integer N
			)
{

Integer i,j;
Real x0,y0,z0,dx,dy,dz;
Real R2,MaxR2;
MaxR2=0;
for(i=0;i<N;i++)
{
	x0 = coors[3*i];
	y0 = coors[3*i+1];
	z0 = coors[3*i+2];

	for(j=i+1;j<N;j++)
	{
			dx = (x0 - coors[3*j]);
			dy = (y0 - coors[3*j+1]);
			dz = (z0 - coors[3*j+2]);
		
			R2 = dx*dx + dy*dy + dz*dz;
				
			if(R2>MaxR2) MaxR2 = R2;
	}//j
}//i

return sqrt(MaxR2);

}

/*
#include "readDoubleTableSimple.h"
#include "Exception.h"
#include <stdlib.h>

main()
{
try{

Real *coors;
Integer nlin,ncol;

readDoubleTableSimple(	"water.XYZ",	//const char *fname,
			&nlin,		//Integer *nlin,	//out
			&ncol,		//Integer *ncol,	//out
			&coors		//Real **result //out, will be allocated
			);


Real R = getMaxDistance( coors, nlin );

printf("%lf\n",R);


free(coors);
} catch(Exception *e) {
	puts(e->toString());
} catch( const char *str ) {
	puts(str);
}

return 0;

}
*/
