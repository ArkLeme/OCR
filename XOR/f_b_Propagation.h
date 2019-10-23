#ifndef F_B_PROPAGATION_H 
#define F_B_PROPAGATION_H
#include "../matrix/matrix.h"
#include "structNet.h"

Matrix* forward_prop(neuNet *network, Matrix * input_data);
void backprop(neuNet* n, int len, Matrix *expOutputs, float learningRate);

#endif
