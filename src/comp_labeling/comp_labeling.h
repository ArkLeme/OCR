#ifndef COMP_LABELING
#define COMP_LABELING

#include "../matrix/matrix_image.h"
#include "union_find.h"

/*
 * Apply the connecting component labeling to our matrix
 * m is the matrix
 * maxLabel the adress of the number of maxLabel (needed outside)
 * return a new matrix
 */
Matrix *CompLabeling(Matrix *m, int* maxLabel);

/*
 * Apply the first pass of the two pass algo
 * m is the matrix we apply first pass
 * maxLabel is the adress of the number of maxLabel
 * return a new matrix
 */
Matrix *FirstPass(Matrix *m, int* maxLabel);

/*
 * Apply the second pass of the two pass algo
 * m is the matrix we apply second pass
 * g the graph of our connected component
 * return a new matrix
 */
Matrix *SecondPass(Matrix *m, Graph *g);

/*
 * Create the graph of our  matrix
 * m is the matrix we want the graph from
 * maxLabel the number of label in our matrix
 * return the graph
 */
Graph *CreateGraph(Matrix *m, int maxLabel);

/*
 * Find the number of usefull label in a matrix
 * m is the matrix
 * ml the max label in the matrix
 * return the number of usefull label
 */
int NumberLabel(Matrix *m, int ml);

/*
 * Reduce the list of label to remove useless label
 * m is the matrix with the albe
 * nbl the number of usefull label
 * ml the max label in the matrix
 * return a list of usefull label
 */
int* LabelReduceList(Matrix *m, int nbl, int ml);

/*
 * reduce the value of label in the matrix
 * m is the matrix
 * *label the list of our usefull label
 * len the len of this list
 */
void ReduceLabel(Matrix *m, int *label, int len);

/*
 * Binsearch in a list
 * list is the list
 * x the element
 * len the length of the list
 * return the index of the element (It must exist)
 */
int BinSearch(int* list, int x, int len);
#endif
