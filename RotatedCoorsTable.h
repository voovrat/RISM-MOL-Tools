#ifndef RotatedCoorsTable_h
#define RotatedCoorsTable_h

#include "Object.h"

class RotatedCoorsTable : public Object 
{
	friend class RotatedCoorsTableIterator;

public:
	Real **m_coorsTable;
	Integer m_Nrotations;
	Real *m_angles;
	
public:
	RotatedCoorsTable()
	{
		m_coorsTable = NULL;
		m_Nrotations = 0;
		m_angles = NULL;
	}

	virtual ~RotatedCoorsTable()
	{
		uninit();
	}
	
	void init(Real *coors,Integer Nsites,Integer Nrotations);
	void uninit();


	Real getAngle(int angleId)
	{
		return m_angles[angleId];
	}

	// NOTE: typically you should not use this function.
	// see RotatedCoorsIterator and ROTATEDCOORS_FOR below
	Real *getCoors(	int phiId, int thetaId, int psiId )
	{
		return m_coorsTable[ psiId + m_Nrotations * ( thetaId + m_Nrotations * phiId ) ];
	}
		
};
// in principle, these FORs can be done with iteratior class:
class RotatedCoorsIterator : public Object
{
friend class RotatedCoorsTable;

protected:
	RotatedCoorsTable *m_rotatedCoorsTable;
public:
	Integer m_phiId,m_thetaId,m_psiId;
	Integer m_Nrotations;
	Real *m_angles;
	Real **m_ptr;
	Integer m_isOver;

public:
	RotatedCoorsIterator( RotatedCoorsTable * rotatedCoorsTable)
	{
		m_rotatedCoorsTable = rotatedCoorsTable;
		m_ptr = rotatedCoorsTable->m_coorsTable;
		m_angles = rotatedCoorsTable->m_angles;
		m_Nrotations = rotatedCoorsTable->m_Nrotations;
		m_isOver = 0;
		m_psiId=0;
		m_thetaId=0;
		m_phiId=0;
	}

	void next()
	{	m_psiId++;
		m_ptr++;
		if(m_psiId>=m_Nrotations) 
		{ 	
			m_psiId = 0; 
			m_thetaId++;
			
			if(m_thetaId>=m_Nrotations)
			{
				m_thetaId =0; 
				m_phiId++;
			
				if(m_phiId>=m_Nrotations)
				{
					m_isOver=1;
				}
			}
		}
	}	
	
	Real *getData() 
	{
		return *m_ptr;
	}

	void setData(Real *data)
	{
		*m_ptr = data;
	}

	Real getPhi()
	{
		return m_angles[m_phiId];
	}

	Real getTheta()
	{
		return m_angles[m_thetaId];
	}

	Real getPsi()
	{
		return m_angles[m_psiId];
	}
	Integer isOver()
	{
		return m_isOver;
	}

};

#define ROTATEDCOORS_FOR(pRotatedCoorsTable) \
{ Real **ROTATEDCOORS_ptr = (pRotatedCoorsTable)->m_coorsTable; \
  Integer ROTATEDCOORS_phiId, ROTATEDCOORS_thetaId, ROTETEDCOORS_psiId; \
  Integer ROTATEDCOORS_N = (pRotatedCoorsTable)->m_Nrotations; \
  Real *ROTATEDCOORS_angles = (pRotatedCoorsTable)->m_angles; \
  for(ROTATEDCOORS_phiId=0; ROTATEDCOORS_phiId<ROTATEDCOORS_N; ROTATEDCOORS_phiId++) \
  for(ROTATEDCOORS_thetaId=0; ROTATEDCOORS_thetaId<ROTATEDCOORS_N; ROTATEDCOORS_thetaId++) \
  for(ROTATEDCOORS_psiId=0; ROTATEDCOORS_psiId<ROTATEDCOORS_N; ROTATEDCOORS_psiId++) {\

#define ROTATEDCOORS_phi	ROTATEDCOORS_angles[ROTATEDCOORS_phiId]
#define ROTATEDCOORS_theta	ROTATEDCOORS_angles[ROTATEDCOORS_thetaId]
#define ROTATEDCOORS_psi	ROTATEDCOORS_angles[ROTATEDCOORS_psiId]
	
#define ROTATEDCOORS_coors 	*ROTATEDCOORS_ptr

#define END_ROTATEDCOORS_FOR  ROTATEDCOORS_ptr++; } }




#endif
