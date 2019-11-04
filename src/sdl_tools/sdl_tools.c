/*
 *Contain sdl function's required for the image treatments.
 */

#include <stdint.h>
#include <err.h>
#include <SDL/SDL.h>
#include "sdl_tools.h"

//Get the reference of a pixel
static inline Uint8* PixelRef(SDL_Surface * InputImage, int x, int y)
{
	int bpp = InputImage->format->BytesPerPixel;
        return (Uint8*)InputImage->pixels + y * InputImage->pitch + x * bpp;
}

//Load an iamge
SDL_Surface* LoadImage(char* path)
{
	SDL_Surface* image = IMG_Load(path);
	if(!image)
	{
		errx(1,"Error path not found: %s\n", path);
	}

	return image;
}

//Save and image and free its surface
void SaveImage(SDL_Surface* InputImage, char* name)
{
	SDL_SaveBMP(InputImage, name);
	SDL_FreeSurface(InputImage);
}

//Copy a surface
SDL_Surface* CopySurface(SDL_Surface* InputImage)
{
	SDL_Surface* OutputImage = CreateSurface(InputImage -> w, InputImage -> h);
	SDL_BlitSurface(InputImage, NULL, OutputImage, NULL);
	return OutputImage;
}

//Create a surface from nothing
SDL_Surface* CreateSurface(int w, int h)
{
	SDL_Surface* OutputImage =
		SDL_CreateRGBSurface(0, w, h,
				32, 0, 0, 0, 0);
	return OutputImage;
}

//Get pixel in a surface
Uint32 GetPixel(SDL_Surface* InputImage, int x, int y)
{
	Uint8* p = PixelRef(InputImage, x, y);

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

//Put pixel in a surface
void PutPixel(SDL_Surface* InputImage, int x, int y, Uint32 pixel)
{
	Uint8* p = PixelRef(InputImage, x, y);

	switch(InputImage->format->BytesPerPixel)
	{
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16 *)p = pixel;
		break;

	case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else
		{
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *)p = pixel;
		break;
	}
}
