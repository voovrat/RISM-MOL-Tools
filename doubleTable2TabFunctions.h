#ifndef doubleTable2TabFunctions_h
#define doubleTable2TabFunctions_h

//Usage:
// /Real *data;
//	Integer i,nlin,ncol;
//
//	readDoubleTable(fname,	//	const char *fname,
//			&nlin,	//Integer *Nrow,	//out
//			&ncol,	//Integer *Ncol,	//out
//			&data 	//Real **result //out, will be allocated
//			);
//
//	TabFunction **fns = new TabFunctions*[ncol-1]; // first column - x
//	for(i=0;i<col-1;i++)	fns[i] = new TabFunction();
//	
// 	doubleTable2TabFunctions(data,nlin,ncol,fns);
//
//	free(data);

class TabFunction;

void doubleTable2TabFunctions(	Real *data,			// line-by-line
				Integer nlin,			
				Integer ncol,
				TabFunction **tabFunctions,	//out. will NOT be allocated
				Real unitKoef = 1		//first column multiplier
				);

#endif
