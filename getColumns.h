#ifndef getColumns_h
#define getColumns_h

void getColumns(Real *matrix, 
		Integer nlin,
		Integer ncol,
		Real *columnData, // out, shuld be pre-allocated of size nlin*ncol*sizeof(Real)
		Real **columns    // out, should be pre-allocated of size ncol*sizeof(Real *)
		);
		


#endif
