#ifndef TOOLS_H
#define TOOLS_H
#include "structNet.h"
#include "../matrix/matrix.h"

void ClearNeuNet(neuNet*n);
void freeNeuNet(neuNet* n);
void Freelayer(layer* cL);
void SaveNeuNet(neuNet* n);
Matrix *Sig(Matrix *m);
Matrix *SigPrime(Matrix *m);
float sigmoid(float x);
float sigPrime(float x);

#endif
