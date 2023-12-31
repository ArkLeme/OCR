#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include "../sdl_tools/sdl_tools.h"

/**
 * \file preprocessing.h
 * \brief header of preprocessing.c
 * \author William.G
 */

/*
 * Apply grayscale to our surface
 * InputImage is the surface we apply the grayscale to
 * return a new surface
 */
SDL_Surface* GrayScale(SDL_Surface* InputImage);

/*
 * Apply histogramm equalization to an surface
 * InputImage is the surface we apply the equalization to
 * return a new surface
 */
SDL_Surface* Contrast(SDL_Surface* InputImage);

/*
 * Apply otsu method to find a good threshold
 * InputImage is the surface we apply otsu to
 * and the new surface
 */
SDL_Surface* Otsu(SDL_Surface* InputImage);

/*
 * Create an binzarize surface depending on a threshold
 * InputImage is the surface we binarize
 * threshold is the threshold to apply binarization
 * return a new surface
 */
SDL_Surface* Binarization(SDL_Surface* InputImage, int threshold);

SDL_Surface* brightness_filter(SDL_Surface* im);
#endif
