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
double sigmoid(float x);
double sigPrime(float x);
Matrix *softmax(Matrix *input);
double Soft(double sum, float z);
Matrix *softprime(Matrix* input);
double Soft_prime(double sum, float z);
void FreeP(Pool*p);

#endif
