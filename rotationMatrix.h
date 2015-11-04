#ifndef rotationMatrix_h
#define rotationMatrix_h

// generates rotation matrix for euler angles psi theta phi

void rotationMatrix(	double psi,   // rotX
			double theta, // rotY
			double phi,   // rotZ
			double *result // 3x3 matrix, xstep=1, ystep=3
			);

//  R = rotX * rotY * rotZ

#endif

