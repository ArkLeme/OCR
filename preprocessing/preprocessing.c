// Include lib required

#include <stdlib.h>
#include "preprocessing.h"

// return a copy of an image after applying grayscale

SDL_Surface* grayscale(SDL_Surface* InputImage)
{
	Uint32 var = GetPixel(InputImage, 0, 0);
	printf("W = %i, var = %ui", InputImage -> w, var);
	return InputImage;
}
