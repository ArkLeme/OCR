#ifndef MATRIX_IMAGE
#define MATRIX_IMAGE

#include "../matrix/matrix.h"
#include "../sdl_tools/sdl_tools.h"

/*
 * Save matrix as image
 * m is a pointeur to the matrix
 * path is the path to save the image
*/
void SaveMatAsIm(Matrix *m, char* path);

/*
 * Create matrix from image
 * InputImage is the surface we want to create the matrix from
*/
Matrix* GetMatFromIm(SDL_Surface* InputImage);

/*
 * Save matrix as iamge using random color
 * m is a pointeur to the matrix
 * path is the path to save the image
 * label is the number of different color we want
*/
void SaveMatAsImRand(Matrix *m, char* path, int label);

/*
 * Save matrix stock in a list
 * l is a list of matrix
 * stop is the number of matrix we want to save
*/
void SaveMatsAsIm(List* l, int stop, char* path);

/*
 * Swap matrix pixel if there is more black than white
 * m is the matrix
 */
void SwapColor(Matrix *m);
#endif
