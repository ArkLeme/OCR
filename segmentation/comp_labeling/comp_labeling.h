#ifndef COMP_LABELING
#define COMP_LABELING

#include "../../matrix/matrix_image.h"
#include "../../matrix/matrix.h"
#include "union_find.h"

Matrix FirstPass(Matrix m, int* maxLabel);

Graph CreateGraph(int size);

#endif
