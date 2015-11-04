#ifndef PotentialCutoff_h
#define PotentialCutoff_h

#include "SiteSitePotential.h"

// Volodymyr P. Sergiievskyi, voov.rat@gmail.com
//
// Return the U(r) - U(r_cut) if r<r_cut and 0 if r>r_cut
//
// U, r_cut are given

// Units: Hartree, Bohr (as everywhere)

class PotentialCutoff : public SiteSitePotential
{
protected:

	SiteSitePotential *m_potential;
	Real m_cutoffDistance;
	Real *m_cutoffCorrections;

	Integer m_numSoluteSites, m_numSolventSites;

public:
	PotentialCutoff( SiteSitePotential *potential, Real cutoffDistance);
	virtual ~PotentialCutoff();

	virtual Real calculatePotential(Integer soluteSite,Integer solventSite,Real R);

	virtual Integer getNumSoluteSites()
	{
		return m_numSoluteSites;
	}

	virtual Integer getNumSolventSites()
	{
		return m_numSolventSites;
	}

};

#endif
