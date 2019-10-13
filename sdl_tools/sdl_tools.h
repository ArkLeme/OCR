#ifndef SDL_TOOLS
#define SDL_TOOLS

#include <SDL.h>
#include <SDL_image.h>

//Load Image
SDL_Surface* LoadImage(char* path);

//Save Image
void SaveImage(SDL_Surface* InputImage, char* name);

//Copy Surface
SDL_Surface* CopySurface(SDL_Surface*);

//Create Surface
SDL_Surface* CreateSurface();

//Get a pixel
Uint32 GetPixel(SDL_Surface* InputImage, int x, int y);

//Put a pixel
void PutPixel(SDL_Surface* InputImage, int x, int y, Uint32 pixel);

#endif
