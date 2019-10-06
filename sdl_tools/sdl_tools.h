#ifndef SDL_TOOLS
#define SDL_TOOLS

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

Uint32 getpixel(SDL_Surface* InputImage, int x, int y);
void putpixel(SDL_Surface* InputImage, int x, int y, Uint32 pixel);

#endif
