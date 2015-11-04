#include "NgSiteSitePotential.h"

#include <math.h>

#include "Settings.h"

Real	NgSiteSitePotential::calculateNgPotential( 	
					Real q1, 
					Real q2, 
					Real erfCoefficient, 
					Real k
					)
{

	if(k<MIN_K) k=MIN_K;

	Real k2 = k*k;
	Real t2 = erfCoefficient * erfCoefficient;

	return  4 * M_PI * q1*q2 / k2 *exp(-k2/4/ t2); 


}



Real NgSiteSitePotential::calculatePotential(Integer soluteSite,Integer solventSite,Real k)
{
	Real q1 = m_soluteCharges->getCharge()[soluteSite];
	Real q2 = m_solventCharges->getCharge()[solventSite];

	return calculateNgPotential( 	q1,			//Real q1, 
					q2,			//Real q2, 
					m_erfCoefficient,	//Real erfCoefficient, 
					k			//Real k
					);

}

