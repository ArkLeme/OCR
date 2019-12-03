#ifndef SEGMENTATION_IMAGE
#define SEGMENTATION_IMAGE

#include <stdio.h>
#include <stdint.h>
#include <err.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../sdl_tools/sdl_tools.h"

/**
 * \file segmentation.h
 * \brief header of segmentation.c
 * \author Alexandre.L
 */

/*
 * Lines segmentation of the image.
 * SDL_Surface* img : The image.
 * return void
 */

void image_lines_segmentation(SDL_Surface* img);

/*
 * Words segmentation of the image.
 * SDL_Surface* img : The image.
 * int begin : Pos of the first line of the line.
 * int end : Pos of the last line of the line.
 * return void
 */

void image_words_segmentation(SDL_Surface *img, int begin, int end);

#endif
