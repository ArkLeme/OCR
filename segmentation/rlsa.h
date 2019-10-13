#ifndef RLSA
#define RLSA
#include "../matrix/matrix.h"
#include "../sdl_tools/sdl_tools.h"

//Save matrix as image
void SaveMatAsIm(Matrix m, char* path);

//Load matrix from image
Matrix GetMatFromIm(SDL_Surface* InputImag);
#endif
