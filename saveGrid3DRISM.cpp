#include <stdlib.h>

#include "saveGrid3DRISM.h"

#include "Grid3DRISM.h"
#include "writeDoubleArrayToFile.h"

void saveGrid3DRISM(	Grid3DRISM *grid,
			const char *fileNamePrefix,
			const char *fileNameSuffix)
{
char str[256];

Real *gridX = (Real *)malloc(grid->getNx() * sizeof(Real));
Real *gridY = (Real *)malloc(grid->getNy() * sizeof(Real));
Real *gridZ = (Real *)malloc(grid->getNz() * sizeof(Real));

generateGridDimension(grid->getNx(),grid->getDRx(),gridX);
generateGridDimension(grid->getNy(),grid->getDRy(),gridY);
generateGridDimension(grid->getNz(),grid->getDRz(),gridZ);

sprintf(str,"%sX%s",fileNamePrefix,fileNameSuffix);
writeDoubleArrayToFile(str,gridX,grid->getNx());

sprintf(str,"%sY%s",fileNamePrefix,fileNameSuffix);
writeDoubleArrayToFile(str,gridY,grid->getNy());

sprintf(str,"%sZ%s",fileNamePrefix,fileNameSuffix);
writeDoubleArrayToFile(str,gridZ,grid->getNz());

free(gridX);
free(gridY);
free(gridZ);

Real *gridKx = (Real *)malloc(grid->getNKx() * sizeof(Real));
Real *gridKy = (Real *)malloc(grid->getNKy() * sizeof(Real));
Real *gridKz = (Real *)malloc( grid->getNKz()*sizeof(Real));

generateGridKx(grid->getNx(),grid->getDKx(),gridKx);
generateGridKy(grid->getNy(),grid->getDKy(),gridKy);
generateGridKz(grid->getNz(),grid->getDKz(),gridKz);

sprintf(str,"%sKx%s",fileNamePrefix,fileNameSuffix);
writeDoubleArrayToFile(str,gridKx,grid->getNKx());

sprintf(str,"%sKy%s",fileNamePrefix,fileNameSuffix);
writeDoubleArrayToFile(str,gridKy,grid->getNKy());

sprintf(str,"%sKz%s",fileNamePrefix,fileNameSuffix);
writeDoubleArrayToFile(str,gridKz,grid->getNKz());

free(gridKx);
free(gridKy);
free(gridKz);

}

