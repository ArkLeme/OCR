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
float Soft(float sum, float z);
Matrix *softprime(Matrix* input);
float Soft_prime(float sum, float z);


#endif
