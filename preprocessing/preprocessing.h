#ifndef PREPROCESSING
#define PREPROCESSING

#include "../sdl_tools/sdl_tools.h"

//Apply grayscale
SDL_Surface* GrayScale(SDL_Surface* InputImage);

//Apply histo method
SDL_Surface* Contrast(SDL_Surface* InputImage);

//Apply otsu's method
SDL_Surface* Otsu(SDL_Surface* InputImage);

//Apply binaryzation on an image depending of the threshold
SDL_Surface* Binarization(SDL_Surface* InputImage, int threshold);
#endif
