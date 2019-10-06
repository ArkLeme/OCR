/*
 *Contain sdl function's required for the image treatments.
 */

#include "sdl_tools.h"
#include <stdint.h>

static inline Uint8* pixelref(SDL_Surface * InputImage, int x, int y)
{
	int bpp = InputImage->format->BytesPerPixel;
        return (Uint8*)InputImage->pixels + y * InputImage->pitch + x * bpp;
}

Uint32 getpixel(SDL_Surface* InputImage, int x, int y)
{
	Uint8* p = pixelref(InputImage, x, y);

	switch(InputImage->format->BytesPerPixel)
	{
	case 1:
		return *p;

	case 2:
		return *(Uint16 *)p;

	case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8| p[2];
		else
			return p[0] | p[1] << 8| p[2] << 16;
	case 4:
		return *(Uint32 *)p;

	default:
		return 0; //Should not happen, but avoids warnings
	}
}
