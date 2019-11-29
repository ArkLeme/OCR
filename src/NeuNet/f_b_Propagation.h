#ifndef F_B_PROPAGATION_H 
#define F_B_PROPAGATION_H
#include "../matrix/matrix.h"
#include "structNet.h"

Matrix* forward_prop(neuNet *network, Matrix * input_data);
void backprop(neuNet* n, int len, Matrix *expOutputs, float learningRate);


void FinalUpdate_batch(neuNet *network, float learning_rate, int batchSize);
void backprop_batch(neuNet *network, Matrix *expOutputs);

#endif
