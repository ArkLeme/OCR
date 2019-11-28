#ifndef F_B_PROPAGATION_H 
#define F_B_PROPAGATION_H
#include "../matrix/matrix.h"
#include "structNet.h"

void forward_prop_actiTest(neuNet* network, Matrix *input_data, char fct);
Matrix* forward_prop(neuNet *network, Matrix * input_data);
void backprop(neuNet* n, int len, Matrix *expOutputs, float learningRate);


void FinalUpdate_batch(neuNet *network, float learning_rate, int batchSize);
void backprop_batch(neuNet *network, Matrix *expOutputs);
void backprop_batch_actiTest(neuNet *network, Matrix *expOutputs, char fct);

#endif
