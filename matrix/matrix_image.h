#ifndef MATRIX_IMAGE
#define MATRIX_IMAGE

#include "../matrix/matrix.h"
#include "../sdl_tools/sdl_tools.h"

//Save matrix as image
void SaveMatAsIm(Matrix m, char* path);

//Load matrix from image
Matrix GetMatFromIm(SDL_Surface* InputImage);

//Save matrix as image and set random color
void SaveMatAsImRand(Matrix m, char* path, int label);
#endif
