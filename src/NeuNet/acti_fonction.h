#ifndef ACTI_FONCTION_H
#define ACTI_FONCTION_H
#include "structNet.h"
#include "../matrix/matrix.h"


Matrix* Acti(Matrix *m, char fct);
Matrix *Sig(Matrix *m);
Matrix *SigPrime(Matrix *m);
double sigmoid(float x);
double sigPrime(float x);

Matrix *Softmax(Matrix* input);
double Soft(double sum, double z, double shift);
Matrix *softprime(Matrix* input);
double Soft_prime(double sum, double z, int delta, double shift);
Matrix *Addition_soft(Matrix* input);

double tan(double x);
double tanPrime(double x);
double ReLU(double x);
double ReLU_prime(double x);

#endif
