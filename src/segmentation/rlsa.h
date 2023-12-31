#ifndef RLSA
#define RLSA

#include "../matrix/matrix.h"

/**
 * \file rlsa.h
 * \brief header of rlsa.c
 * \author William.G
 */

/*
 * Apply horizontal lrsa
 * m is the matrix
 * limit is the threshold value
 * return a new matrix
 */
Matrix *Hrlsa(Matrix *m, int limit);

/*
 * Apply vertical lrsa
 * m is the matrix
 * limit is the treshold value
 * return a new matrix
 */
Matrix *Vrlsa(Matrix *m, int limit);

/*
 * Apply both vertical and horizontal lrsa
 * m is the matrix
 * limit is the treshold value
 * return a new matrix
 */
Matrix *rlsa(Matrix *m, int vr, int cr);

#endif
