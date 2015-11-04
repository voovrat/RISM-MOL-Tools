#include "SphericalFFT.h"
#include "Grid1DRISM.h"

#include <stdlib.h>
#include <string.h>

#include "GridDataFactory.h"
#include "GridIndex.h"
#include "GridComparator1DRISM.h"

#include "Settings.h"
#include "fftw3.h"

using namespace std;


class SphericalFFTData : public Object
{
public:
	SphericalFFTData(Grid1DRISM *g3d);
	virtual ~SphericalFFTData();

	Integer m_N;
	Real m_dR,m_dk;
	Integer m_sizeOfData;

	Real *m_inputData;
	Real *m_outputData;
	
	fftw_plan	m_dstPlan;

	void setInput(Real *in);
	void getOutput(Real *out);

	void dst();		
	void d3fft();
	void d3ifft();

};

class SphericalFFTDataFactory : public GridDataFactory
{
public:
	static SphericalFFTDataFactory *getInstance()
	{
		static SphericalFFTDataFactory *instance = NULL;
		if(!instance) 
			instance = new SphericalFFTDataFactory();
		return instance;
	
	}

	virtual Object *createData(Grid *grid)
	{
		return new SphericalFFTData((Grid1DRISM*)grid);
	}
};


SphericalFFTData::SphericalFFTData(Grid1DRISM *grid)
{

	m_N = grid->getN();
	m_dR = grid->getDR();
	m_dk = grid->getDK();
	
	m_sizeOfData = m_N * sizeof(Real);

	m_inputData = (Real*)malloc(m_sizeOfData );
	m_outputData = (Real*)malloc(m_sizeOfData);

	m_dstPlan =  fftw_plan_r2r_1d(	m_N,		//int n,
					m_inputData,	//double *in, 
					m_outputData,	//double *out,
					FFTW_RODFT00,	//fftw_r2r_kind kind, -> SphericalFFT
					FFTW_MEASURE	//unsigned flags
					);
}

SphericalFFTData::~SphericalFFTData()
{
	free(m_inputData);
	free(m_outputData);
	fftw_destroy_plan(m_dstPlan);
}

void SphericalFFTData::setInput(Real *in)
{
	memcpy(m_inputData,in,m_sizeOfData);
}


void SphericalFFTData::getOutput(Real *out)
{
	memcpy(out,m_outputData,m_sizeOfData);
}

void SphericalFFTData::dst()
{
	fftw_execute( m_dstPlan );
}

void SphericalFFTData::d3fft()
{
	Real r,k;
	Integer N;
	Real *data;

	//y=4*pi./k.*dst2(x.*r)*dR;


	// x.*r	
	data  = m_inputData;
	for(r=m_dR, N=m_N; N--; r+=m_dR, data++)
	{
		*data*=r;
	}
	// inputData = x.*r
	

	dst();	// outputData = dst(x.*r)

	//y=4*pi./k.*dst2(x.*r)*dR;
	Real koeff = 4*M_PI * m_dR /2;
	data = m_outputData;
	for(k=m_dk, N=m_N; N--; k+=m_dk, data++)
	{
		*data *= koeff/k;
	}
}

void SphericalFFTData::d3ifft()
{
	Real r,k;
	Integer N;
	Real *data;

	//y=1/2/pi^2*dst2(x.*k)./r*dk;

	// x.*k	
	data  = m_inputData;
	for(k=m_dk, N=m_N; N--; k+=m_dk, data++)
	{
		*data*=k;
	}
	// inputData = x.*k
	

	dst();	// outputData = dst(x.*k)

	//y=1/2/pi^2*dst2(x.*k)./r*dk;
	Real koeff = 0.5/M_PI/M_PI * m_dk /2;
	data = m_outputData;
	for(r=m_dR, N=m_N; N--; r+=m_dR, data++)
	{
		*data *= koeff/r;
	}
}


SphericalFFT *SphericalFFT::m_instance = new SphericalFFT();


SphericalFFT *SphericalFFT::getInstance()
{
 	return m_instance;
}

SphericalFFT::SphericalFFT()
{
	m_gridIndex = new GridIndex(	SphericalFFTDataFactory::getInstance(),	//GridDataFactory *gridDataFactory,
				 	GridComparator1DRISM::getInstance()	//GridComparator<Grid> *gridComparator
		);
}

SphericalFFT::~SphericalFFT()
{
	NULL_DELETE(m_gridIndex);
}

Real SphericalFFT::d3fft(Real *in, Real *out,Grid1DRISM *grid)
{
	SphericalFFTData *data = (SphericalFFTData *)m_gridIndex->findData(grid);

	data->setInput(in);
	data->d3fft();	
	data->getOutput(out);

	return 1; 
}

Real SphericalFFT::d3ifft(Real *in, Real *out,Grid1DRISM *grid)
{
	SphericalFFTData *data = (SphericalFFTData *)m_gridIndex->findData(grid);

	data->setInput(in);
	data->d3ifft();	
	data->getOutput(out);
	
	return 1; 
}

void	SphericalFFT::dst( Real *in, Real *out,Grid1DRISM *grid)
{
	SphericalFFTData *data = (SphericalFFTData *)m_gridIndex->findData(grid);
	
	data->setInput(in);
	data->dst();
	data->getOutput(out);
}
