#include "FFTW3D.h"
#include "Grid3DRISM.h"

#include <stdlib.h>
#include <string.h>

#include "GridDataFactory.h"
#include "GridIndex.h"
#include "GridComparator3DRISM.h"

#include "Settings.h"

using namespace std;


class FFTW3DData : public Object
{
public:
	FFTW3DData(Grid3DRISM *g3d);
	virtual ~FFTW3DData();

	Integer m_Nreal,m_Ncomplex;
	Integer m_sizeOfRealData, m_sizeOfComplexData;

	Real *m_realData;
	std::complex<Real> *m_complexData;
	
	fftw_plan	m_forwardPlan,m_inversePlan;

	void setRealInput(Real *in);
	void getRealOutput(Real *out);
	void setComplexInput(std::complex<Real> * in);
	void getComplexOutput(std::complex<Real> * out);

	void fft();
	void ifft();
		

};

class FFTW3DDataFactory : public GridDataFactory
{
public:
	static FFTW3DDataFactory *getInstance()
	{
		static FFTW3DDataFactory *instance = NULL;
		if(!instance) 
			instance = new FFTW3DDataFactory();
		return instance;
	
	}

	virtual Object *createData(Grid *grid)
	{
		return new FFTW3DData((Grid3DRISM*)grid);
	}
};


FFTW3DData::FFTW3DData(Grid3DRISM *g3d)
{

	Integer Nx = g3d->getNx();
	Integer Ny = g3d->getNy();
	Integer Nz = g3d->getNz();

	m_Nreal = Nx*Ny*Nz;
	m_Ncomplex = Nx*Ny*(Nz/2+1);
	m_sizeOfRealData = m_Nreal * sizeof(Real);
	m_sizeOfComplexData = m_Ncomplex *sizeof(complex<Real>);

	m_realData = (Real *)malloc(m_sizeOfRealData );
	m_complexData = (complex<Real>*)malloc(m_sizeOfComplexData);

	m_forwardPlan = fftw_plan_dft_r2c_3d
			(	Nx,		//Integer n0, 
				Ny,		//Integer n1, 
				Nz,		//Integer n2,
				m_realData,	//Real *in,
				(fftw_complex *)m_complexData,	//fftw_complex *out,
				FFTW_MEASURE
			);

	m_inversePlan = fftw_plan_dft_c2r_3d
			(	Nx,		//Integer n0, 
				Ny,		//Integer n1, 
				Nz,		//Integer n2,
				(fftw_complex *)m_complexData,	//Real *in,
				m_realData,	//fftw_complex *out,
				FFTW_MEASURE
			);	
}

FFTW3DData::~FFTW3DData()
{
#if DEBUG_LEAKS
	FILE *f=fopen("leaks.txt","r+");
	fseek(f,0,SEEK_END);
	fprintf(f,"DESTRUCTOR FFTW3DData::~FFTW3DData(): this=%p\n",this);
	fclose(f);
#endif

	free(m_realData);
	free(m_complexData);
	fftw_destroy_plan(m_forwardPlan);
	fftw_destroy_plan(m_inversePlan);
}

void FFTW3DData::setRealInput(Real *in)
{
	memcpy(m_realData,in,m_sizeOfRealData);
}


void FFTW3DData::getRealOutput(Real *out)
{
	memcpy(out,m_realData,m_sizeOfRealData);
}

void FFTW3DData::setComplexInput(complex<Real> * in)
{
	memcpy(m_complexData,in,m_sizeOfComplexData);
}

void FFTW3DData::getComplexOutput(complex<Real> * out)
{
	memcpy(out,m_complexData,m_sizeOfComplexData);
}

void FFTW3DData::fft()
{
	fftw_execute(m_forwardPlan);
}

void FFTW3DData::ifft()
{
	fftw_execute(m_inversePlan);
}



FFTW3D *FFTW3D::m_instance = new FFTW3D();


FFTW3D *FFTW3D::getInstance()
{
 	return m_instance;
}

FFTW3D::FFTW3D()
{
	m_gridIndex = new GridIndex(	FFTW3DDataFactory::getInstance(),	//GridDataFactory *gridDataFactory,
				 	GridComparator3DRISM::getInstance()	//GridComparator<Grid> *gridComparator
		);
}

FFTW3D::~FFTW3D()
{
	NULL_DELETE(m_gridIndex);
}

/*
FFTW3DData *FFTW3D::findData(Grid3DRISM *g3d)
{
	DATA_MAP_ITERATOR it = m_dataMap.find( g3d );
	FFTW3DData *data;

	if(it==m_dataMap.end())
	{
		data = new FFTW3DData(g3d);

		Grid3DRISM *key = (Grid3DRISM *)g3d->clone();
		m_dataMap[key] = data;

		this->addToDeleteList(key);
	}
	else data = (*it).second;

	return data;
}
*/

Real FFTW3D::fft(Real *in,complex<Real> *out,Grid3DRISM *g3d)
{
	FFTW3DData *data = (FFTW3DData *)m_gridIndex->findData(g3d);

	data->setRealInput(in);
	data->fft();	
	data->getComplexOutput(out);

	return g3d->getDRx() * g3d->getDRy() * g3d->getDRz(); 
}

Real FFTW3D::ifft(complex<Real> *in, Real *out, Grid3DRISM *g3d)
{
	FFTW3DData *data = (FFTW3DData *)m_gridIndex->findData(g3d);
	
	data->setComplexInput(in);
	data->ifft();
	data->getRealOutput(out);

	return 1.0/ (	g3d->getNx()  * g3d->getNy()  * g3d->getNz() * 
 			g3d->getDRx() * g3d->getDRy() * g3d->getDRz()
		);
}

