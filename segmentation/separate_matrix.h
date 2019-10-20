#ifndef SEPARATE_MATRIX
#define SEPARATE_MATRIX

PosM** FindPosMat(Matrix *m, int maxLabel);

List* ListOfMat(Matrix* m, PosM** p, int maxLabel);

#endif
