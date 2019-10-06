#ifndef SDL_TOOLS
#define SDL_TOOLS

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

//Load Image
SDL_Surface* LoadImage(char* path);

//get a pixel
Uint32 GetPixel(SDL_Surface* InputImage, int x, int y);

//Put a pixel
void PutPixel(SDL_Surface* InputImage, int x, int y, Uint32 pixel);

#endif
