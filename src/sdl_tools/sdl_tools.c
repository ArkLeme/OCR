/*
 *Contain sdl function's required for the image treatments.
 */

#include <stdint.h>
#include <err.h>
#include "sdl_tools.h"

/**
 * \file sdl_tools.c
 * \brief Every requiered function to use the SDL_Surface, almost all of them
 * are from the documentation of SDL.
 * \author William.G
 */

/**
 * \fn static inline Uint8* PixelRef(SDL_Surface* InputImage, int xn int y)
 * \brief Get the reference of a pixel in an Surface
 *
 * \param InputImage : The surface
 * \param x : x coordinate of the pixel
 * \param y : y coordinate of the pixel
 *
 * \return reference to the pixel
 */
static inline Uint8* PixelRef(SDL_Surface * InputImage, int x, int y)
{
	int bpp = InputImage->format->BytesPerPixel;
        return (Uint8*)InputImage->pixels + y * InputImage->pitch + x * bpp;
}

/**
 * \fn SDL_Surface* LoadImage(char* path)
 * \brief Create a surface from a png
 *
 * \param path : path of the png file
 *
 * \return Surface of the image
 */
SDL_Surface* LoadImage(char* path)
{
	SDL_Surface* image = IMG_Load(path);
	if(!image)
	{
		errx(1,"Error path not found: %s\n", path);
	}

	return image;
}

/**
 * \fn void SaveImage(SDL_Surface* InputImage, char* name)
 * \brief Save and free the memory of a Surface
 *
 * \param InputImage : the Surface to save
 * \param name : path and name of the file to save
 */
void SaveImage(SDL_Surface* InputImage, char* name)
{
	SDL_SaveBMP(InputImage, name);
	SDL_FreeSurface(InputImage);
}

/**
 * \fn SDL_Surface* CopySurface(SDL_Surface* InputImage)
 * \brief Copy a Surface and return a new one
 *
 * \param InputImage : the surface to copy
 *
 * \return New surface, it does not modify InputImage
 */
SDL_Surface* CopySurface(SDL_Surface* InputImage)
{
	SDL_Surface* OutputImage = CreateSurface(InputImage -> w, InputImage -> h);
	SDL_BlitSurface(InputImage, NULL, OutputImage, NULL);
	return OutputImage;
}

/**
 * \fn SDL_Surface* CreateSurface(int w, int h)
 * \brief Create a surface of width w and height h
 *
 * \param w : width of the surface
 * \param h : height of the surface
 *
 * \return New surface
 */
SDL_Surface* CreateSurface(int w, int h)
{
	SDL_Surface* OutputImage =
		SDL_CreateRGBSurface(0, w, h,
				32, 0, 0, 0, 0);
	return OutputImage;
}

/**
 * \fn Uint32 GetPixel(SDL_Surface* InputImage, int x, int y)
 * \brief Get the pixel at coordinate x,y in a Surface
 *
 * \param InputImage : The surface to search
 * \param x : x coordinate of the pixel
 * \param y : y coordinate of the pixel
 *
 * \return Pixel at the x,y position in the surface
 */
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

/**
 * \fn void PutPixel(SDL_Surface* InputImage, int x, int y, Uint32 pixel)
 * \brief Put a pixel at the coordinate x,y in a Surface
 *
 * \param InputImage : The surface to put the pixel
 * \param x : x coordinate of the pixel
 * \param y : y coordinate of the pixel
 * \param pixel : the pixel to insert
 */
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
