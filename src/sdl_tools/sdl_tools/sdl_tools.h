#ifndef SDL_TOOLS_H
#define SDL_TOOLS_H

#include <SDL.h>
#include <SDL_image.h>

/**
 * \file sdl_tools.h
 * \brief header of sdl_tools.c
 * \author William.G
 */

/*
 * Load a surface from an image
 * path is the path of our image
 * return a surface
 */
SDL_Surface* LoadImage(char* path);

/*
 * Save an image from a surface
 * InputImage is the surface
 * path the path to save the image
 */
void SaveImage(SDL_Surface* InputImage, char* path);

/*
 * Copy a surface
 * InputImage is the surface we copy
 * return a new surface
 */
SDL_Surface* CopySurface(SDL_Surface* InputImage);

/*
 * Create a surface from nothing
 * x is the number of col
 * y the number of line
 * return a new surface
 */
SDL_Surface* CreateSurface(int x, int y);

/*
 * Get a pixel in a surface
 * x is the col position
 * y the line position
 * return the pixel
 */
Uint32 GetPixel(SDL_Surface* InputImage, int x, int y);

/*
 * Put a pixel in surface
 * x is the col position
 * y the line position
 * pixel the pixel we insert
 */
void PutPixel(SDL_Surface* InputImage, int x, int y, Uint32 pixel);

#endif
