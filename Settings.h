#ifndef Settings_h
#define Settings_h

typedef double Real;
typedef long Integer;

// constants

#define MIN_DISTANCE 	0.01
#define MIN_K 		1e-4

#define MIN_DETERMINANT	1e-12
#define MAX_COND	1e+10 
#define COARSE_POT_CUT 8 //Bohr
#define BIG_POT 1e12
#define G_TRESHOLD 0.5

#define AVERAGING_DIVIDER  7// for use in buildPotential2
#define MIN_DR 		  (0.5/0.52) // minimal spacing for using buildPotential4 


#define MULTIPLY_CHI_BY_SINC 0

#define VERBOSE_SCAL_PROD_NORM 1

// Debug

#define DEBUG_LEAKS 0
#define DEBUG_STRANGE_04 0
#define DEBUG_DIIS_DECAYFACTOR 0
#define DEBUG_FREE_ENERGY 0
#define NO_THETA	0
#define DEBUG_TESTBUILDSPHERICALK2 0
#define DEBUG_NaN 	0
#define DEBUG_CHI	0
#define DEBUG_BRIDGE	0
#define DEBUG_POTENTIAL 0

// FFT 3D

#define USE_FFT_DELTA 1
#define USE_FFT_ZERO 0

// buildchi

#define USE_buildChi4 1   // omega and h_solv in Fourier sapce 
#define USE_buildChi3 0   // omega and h_solv in real space


// buildSpherical

#define USE_buildSpherical  1
#define USE_buildSpherical2 0
#define USE_buildSpherical4 0 // for buildChi3: maxes of RDF are mostly conserved 

// drawDeltaSphere

#define USE_REAL_OMEGA  0	

//if real omega
#define USE_drawDeltaSphere3 1	// simple 0-1
#define USE_drawDeltaSphere4 0	// proportional to the sphere-cell cross sections
#define USE_drawDeltaSphere5 0 // assumes linear interpolation for c

// else
#define USE_buildKSphere 1 // omega in k space (sin kr/kr)

// buildPotential

#define USE_buildPotential  0
#define USE_buildPotential2 0 	// with averaging over grid cell
#define AVERAGE_EXP_POTENTIAL  0

#define USE_buildPotential4 1



// buildTheta

#define USE_buildAnalyticalTheta 1 

//DIIS

#define USE_DIIS_updateGridDifference 0
#define DIIS_MAX_SKIP_COUNT 10
#define DIIS_PRE_DAMPING  0.3
#define DIIS_POST_DAMPING 0.5

#include <time.h>
typedef time_t Time;

#endif
