#ifndef SEPARATE_MATRIX
#define SEPARATE_MATRIX

#include "../matrix/matrix.h"

/*
 * Find the position of all matrix and return a pointeur to the list of pos
 * m is the initial matrix
 * maxlabel the number of different component
 * return a pointeur to the list of position
 */
PosM** FindPosMat(Matrix *m, int maxLabel);

/*
 * Create a list of matrix and their position
 * m is the initial matrix
 * p the pointeur to the list of position
 * maxLabel the number of components in the initial matrix
 * return a pointeur to the list
 */
List* ListOfMat(Matrix* m, PosM** p, int maxLabel);

#endif
