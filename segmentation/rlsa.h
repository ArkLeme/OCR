#ifndef RLSA
#define RLSA

#include "../matrix/matrix.h"

//Apply horizontal rlsa
Matrix Hrlsa(Matrix m, int limit);

//Apply vertical rlsa
Matrix Vrlsa(Matrix m, int limit);

//Apply lrsa
Matrix rlsa(Matrix m, int limit);

Matrix rlsa_vertical(Matrix m, int limit);
#endif
