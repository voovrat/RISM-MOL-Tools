#include "buildPotentialK.h"

#include "MoleculeCoordinates.h"
#include "SiteSitePotential.h"
#include "Solution3DRISMK.h"

// fourier transform of spherically symmetric function is spherically symmetric
// [Gosta H Granlund, Hans Knutsson. Signal Processing for Computer Vision. 
// Kulwer Academic Publishers, Dordecht, Netherlands. section 4.4.3 ]
// 
// \Integer f(x-a,y-b,z-c)exp(-ik_x x -ik_y y -ik_z z) dxdydz = [ x'=x-a, y'=y-b, z'=z-c ] =
// exp(-i(k_x a + k_y b + k_z c)) \Integer f(x',y',z') exp(-ik_x x' -ik_y y' -ik_z z')dx'dy'dz'
//

void buildPotentialK (
	MoleculeCoordinates *soluteCoors,
	SiteSitePotential *siteSitePotential,
	Solution3DRISMK *potential // output
)
{

if(!potential->getData())
	potential->createGamma();

Integer soluteSite, solventSite;
Integer NSolventSites = siteSitePotential->getNumSolventSites();
Integer NSoluteSites = siteSitePotential->getNumSoluteSites();

//complex<Real> complex_i(0,1);

for(solventSite = 0; solventSite < NSolventSites; solventSite++)
{
	KGAMMA_FOR_SOLUTION(potential,solventSite)
	{		

		Real kx = KGAMMA_FOR_KX;
		Real ky = KGAMMA_FOR_KY;
		Real kz = KGAMMA_FOR_KZ;

		Real KR = sqrt(kx*kx + ky*ky + kz*kz);	

	 	KGAMMA_FOR_DATA = 0;
		for(soluteSite=	0; soluteSite <NSoluteSites; soluteSite++)
		{
	
			Real dx = soluteCoors->getX()[soluteSite];
			Real dy = soluteCoors->getY()[soluteSite];
			Real dz = soluteCoors->getZ()[soluteSite];

			Real radial =  siteSitePotential->calculatePotential(
					soluteSite, 
					solventSite,
					KR);

			//dx = 1;
			Real arg = kx*dx + ky*dy + kz*dz;
			complex<Real> phase(cos(arg),-sin(arg));

			//complex<Real> phase = -complex_i * sin(kx*dx + ky*dy + kz*dz)
 			//			+ complex_i * cos(kx*dy+ky*dy+kz*dz);
						;//exp( 
					//-complex_i* (kx*dx + ky*dy + kz*dz) 
					//);

			KGAMMA_FOR_DATA += radial * phase;
			//KGAMMA_FOR_DATA = phase;

		} // soluteSite
	}
	END_KGAMMA_FOR_SOLUTION   

}//for solventSite


}
