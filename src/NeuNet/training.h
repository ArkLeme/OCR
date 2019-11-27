#ifndef TRAINING_H
#define TRAINING_H

#include "structNet.h"

int GetOutput(neuNet *n);
Pool** CreateBatches(Pool*p, size_t batchSize);
void Training(neuNet* n, int epoch, double learning_rate);

#endif
