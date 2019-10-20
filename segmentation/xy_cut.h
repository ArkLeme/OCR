#ifndef XY_CUT
#define XY_CUT

#include "../matrix/matrix.h"

//Fill line
void FillLine(Matrix *m, int i, int start, int end);

//Fill col
void FillCol(Matrix *m, int j, int start, int end);

//Cut on X axis
void XCut(Matrix *m);

//Cut on Y axis;
void YCut(Matrix *m);
#endif
