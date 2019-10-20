#ifndef COMP_LABELING
#define COMP_LABELING

#include "../../matrix/matrix_image.h"
#include "../../matrix/matrix.h"
#include "union_find.h"

//Create matrix with label
Matrix *CompLabeling(Matrix *m, int* maxLabel);

//First pass of the two pass algo
Matrix *FirstPass(Matrix *m, int* maxLabel);

//Second pass
Matrix *SecondPass(Matrix *m, Graph *g);

//Create graph of subset
Graph *CreateGraph(Matrix *m, int maxLabel);

//Count label
int NumberLabel(Matrix *m, int ml);

int* LabelReduceList(Matrix *m, int nbl, int ml);

void ReduceLabel(Matrix *m, int *label, int len);

int BinSearch(int* list, int x, int len);
#endif
