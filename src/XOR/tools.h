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

Matrix *Softmax(Matrix* input);
double Soft(double sum, double z, double shift);
Matrix *softprime(Matrix* input);
double Soft_prime(double sum, double z, int delta, double shift);
Matrix *Addition_soft(Matrix* input);

Pool* InitPool(size_t size);
void FreePool(Pool*p);

#endif
