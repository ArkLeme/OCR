#ifndef  PROPA_TEST_H
#define  PROPA_TEST_H

void forward_prop_actiTest(neuNet* network, Matrix *input_data, char fct);
void backprop_batch_actiTest(neuNet *network, Matrix *expOutputs, char acti_fct);

#endif
