#ifndef PREPROCESSING
#define PREPROCESSING

#include "../sdl_tools/sdl_tools.h"

//Apply grayscale
SDL_Surface* GrayScale(SDL_Surface* InputImage);

//Apply histo method
SDL_Surface* Contrast(SDL_Surface* InputImage);

#endif
