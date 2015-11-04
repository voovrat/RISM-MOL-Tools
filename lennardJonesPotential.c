#include "lennardJonesPotential.h"

#include "Settings.h"

double lennardJonesPotential(double sigma12, double epsilon12, double R)
{
if(R<MIN_DISTANCE)  R=MIN_DISTANCE;

double SR = sigma12/R;
double SR3 = SR*SR*SR;
double SR6 = SR3*SR3;
double SR12 = SR6*SR6;

return 4*epsilon12 * ( SR12 - SR6 );

}

