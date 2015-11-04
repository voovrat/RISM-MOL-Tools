#include "interpolateSolution3DRISMR.h"

#include "Solution3DRISMR.h"
#include "Exception.h"
#include "interpolate3_3DRISM.h"
#include "Grid3DRISM.h"

void interpolateSolution3DRISMR(Solution *coarse0,
				Solution *fine0
			)
{
Solution3DRISMR *fineSolution = dynamic_cast<Solution3DRISMR *>(fine0);
Solution3DRISMR *coarseSolution = dynamic_cast<Solution3DRISMR *>(coarse0);



Integer numSites = coarseSolution->getNumberOfSites();

Grid3DRISM *coarseGrid = (Grid3DRISM *)coarseSolution->getGrid();
Grid3DRISM *fineGrid = (Grid3DRISM *)fineSolution->getGrid();

if(  	coarseGrid->getNx() * 2 != fineGrid->getNx() ||
	coarseGrid->getNx() * 2 != fineGrid->getNx() ||
	coarseGrid->getNx() * 2 != fineGrid->getNx() )
	throw new Exception(NULL,"interpolate3DRISMR : the size of the fine grid should be twice larger than the size of the coarse grid");

Integer i;
for(i=0;i<numSites;i++)
{

	//interpolation in x direction, 
	// row->y , col ->z
	interpolate3_3DRISM<Real>(
		coarseSolution->getGamma()[i],	//T *src,
		coarseGrid->getNx(),		//Integer N, //for 1D interp
		coarseGrid->getNy() * coarseGrid->getNz(), //Integer src_stride,
		fineGrid->getNy() * fineGrid->getNz(), //Integer fine_stride,
		coarseGrid->getNy(),	//row->y Integer Nrow,
		coarseGrid->getNz(),	//col->z Integer Ncol,
		0,			//src_row_inc
		1,			//src_col_inc
		fineGrid->getNz(),	//omit each second row Integer dst_row_inc, // inside 1 cycle
		2,			// omit each second colInteger dst_col_inc  // inside 2 cycles
		fineSolution->getGamma()[i] //T *dst//out
	);

	//interpolation in y direction
	// row->x, col->z 
	interpolate3_3DRISM<Real>(
		fineSolution->getGamma()[i],	//T *coarse,
		coarseGrid->getNy(),		//Integer N, //for 1D interp
		2*fineGrid->getNz(), 		//Integer src_stride,
		fineGrid->getNz(), 	//Integer dst_stride,
		fineGrid->getNx(),	//row->x Integer Nrow,
		coarseGrid->getNz(),	//col->z Integer Ncol,
		fineGrid->getNz()*(fineGrid->getNy()-1), //src_row_inc
		2,					//src_col_inc
		fineGrid->getNz()*(fineGrid->getNy()-1),	//reset to the next x-level  Integer dst_row_inc, // inside 1 cycle
		2,			// omit each second colInteger dst_col_inc  // inside 	2 cycles
		fineSolution->getGamma()[i] //T *fine//out
		);


	//interpolation in z direction
	// row->x, col->y 
	interpolate3_3DRISM<Real>(
		fineSolution->getGamma()[i],	//T *coarse,
		coarseGrid->getNz(),		//Integer N, //for 1D interp
		2,	 		//Integer src_stride,
		1,	 	//Integer dst_stride,
		fineGrid->getNx(),	//row->x Integer Nrow,
		fineGrid->getNy(),	//col->z Integer Ncol,
		0,			 //src_row_inc
		fineGrid->getNz(),	//src_col_inc
		0,			//  Integer dst_row_inc, // inside 1 cycle
		fineGrid->getNz(),	//dst_col_inc  // inside 2 cycles
		fineSolution->getGamma()[i] //T *fine//out
		);
}

}
